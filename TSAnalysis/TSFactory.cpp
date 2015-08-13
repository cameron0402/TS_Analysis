#include "TSFactory.h"
#include "TSData.h"
#include "PES/AdaptationField.h"

Stream::Stream(PMT::StreamInfo* si)
    : stream_pid(si->elem_PID),
      scrambling(false),
      pts_list(MAX_PTS_NUM),
      dts_list(MAX_DTS_NUM)
{
    int i = 0;
    for(;;i++)
    {
        if(STREAM_TYPE_TABLE[i].stream_type == 0xFF)
            break;
        if(STREAM_TYPE_TABLE[i].stream_type == si->type)
        {
            stream_type = &STREAM_TYPE_TABLE[i];
            break;
        }
    }
    std::list<Descriptor*>::iterator dit = si->desc_list.begin();
    for(; dit != si->desc_list.end(); ++dit)
    {
        if((*dit)->tag == 0x09) //CA_descriptor
        {
            scrambling = true;
            break;
        }
    }
}

Stream::~Stream()
{
}

ProgInfo::ProgInfo(uint8_t* data)
    : program_number((data[0] << 8) | data[1]),
      program_map_PID(((data[2] & 0x1F) << 8) | data[3]),
      pcr_pid(0x1FFF),
      scrambling(false),
      pcr_list(MAX_PCR_NUM),
      pcr_pkt_list(MAX_PCR_NUM),
      stream_list()
{
}

void ProgInfo::setInfo(PMT* pt)
{
    pcr_pid = pt->PCR_PID;
    std::list<Descriptor*>::iterator dit = pt->desc_list.begin();
    for(; dit != pt->desc_list.end(); ++dit)
    {
        if((*dit)->tag == 0x09) //CA_descriptor
        {
            scrambling = true;
            break;
        }
    }

    std::list<PMT::StreamInfo*>::iterator si = pt->stream_list.begin();
    for(; si != pt->stream_list.end(); ++si)
    {
        Stream* sm = new Stream(*si);
        stream_list.push_back(sm);
        if(scrambling)
        {
            sm->scrambling = true;
        }
    }
}

ProgInfo::~ProgInfo()
{
    std::list<Stream*>::iterator si = stream_list.begin();
    for(; si != stream_list.end(); ++si)
        delete (*si);
    stream_list.clear();
}

TSFactory* TSFactory::_instance = NULL;

//##ModelId=5555501D00F6
bool TSFactory::addSection(Section* section)
{
    return section->joinTo(this);
}

//it's a simple version of TSGather without any check
void TSFactory::ESGather(int pid, uint8_t* ts_packet, std::ofstream& of)
{
    uint8_t* payload_pos = NULL;
    uint8_t* p_new_pos = NULL;
    bool first_flag = false;
    uint8_t expected_counter;
    uint8_t available_length;
    uint8_t adp_ctr = 0;

    if(raw_sarr[pid] == NULL)
    {
        raw_sarr[pid] = new TSData(TSData::PESDATA);
    }

    TSData* raw_ts = raw_sarr[pid];

    raw_ts->PID = ((ts_packet[1] & 0x1F) << 8) | ts_packet[2];

    /* Skip the adaptation_field if present */
    if(ts_packet[3] & 0x20)
        payload_pos = ts_packet + 5 + ts_packet[4];
    else
        payload_pos = ts_packet + 4;

    /* Return if no payload in the TS packet */
    if(!(ts_packet[3] & 0x10))
        return ;

    /* Unit start -> save the last pes packet first and then start a new one */
    if(ts_packet[1] & 0x40)
    {
        if(raw_ts->recv_length != 0)
        {
            raw_ts->getPES();
            if(raw_ts->pes->PES_packet_data_length != 0)
            {
                of.write((const char*)raw_ts->pes->PES_packet_data, raw_ts->recv_length - raw_ts->pes->PES_packet_data_length);
            }
            raw_ts->Reset();
        }
        raw_ts->recv_flag = true;
    }

    if(raw_ts->recv_flag)
    {
        available_length = 188 + ts_packet - payload_pos;
        if(available_length > 0)
        {
            if(raw_ts->recv_length + available_length > raw_ts->ts_data_length)
            {
                raw_ts->ts_data_length += TSData::MAX_TS_LENGTH;
                raw_ts->ts_data = (uint8_t*)realloc(raw_ts->ts_data, raw_ts->ts_data_length);
                raw_ts->pes->raw_data = raw_ts->ts_data;
            }
            memcpy(raw_ts->ts_data + raw_ts->recv_length, payload_pos, available_length);
            raw_ts->recv_length += available_length;
        }
    }
    
    return ;
}

int TSFactory::adaptationFieldAnalysis(uint8_t* ts_packet, TSData* raw_ts,
                                        bool& pcr_inv_err, bool& pcr_dis_err, bool& pcr_acu_err)
{
    int adp_len = 0;
    AdaptationField* adf = new AdaptationField(ts_packet + 4);
    if(adf->PCR_flag)
    {
        int64_t pcr = adf->program_clock_reference_base * 300 + adf->program_clock_reference_extension;
        if(pat != NULL)
        {
            std::list<ProgInfo*>::iterator pit = pat->prog_list.begin();
            for(; pit != pat->prog_list.end(); ++pit)
            {
                if((*pit)->pcr_pid == raw_ts->PID)
                {
                    int idx = (*pit)->pcr_list.Size() - 1;
                    if(idx > 0)
                    {
                        int64_t pcr_pre = (*pit)->pcr_list[idx];
                        int64_t pcr_intv = pcr - pcr_pre;
                        double inv = double(pcr_intv) / 27000;
                        int64_t pcr_excp_intv = ((*pit)->pcr_list[idx] - (*pit)->pcr_list[idx - 1]) *
                                                (pkt_num - (*pit)->pcr_pkt_list[idx]) /
                                                ((*pit)->pcr_pkt_list[idx] - (*pit)->pcr_pkt_list[idx - 1]);

                        if(pcr_excp_intv - pcr_intv >= 14 || pcr_excp_intv - pcr_intv <= -14)
                            pcr_acu_err = true;

                        if(inv > 100 && !adf->discontinuity_indicator)
                            pcr_dis_err = true;

                        if(inv > 40)
                            pcr_inv_err = true;

                        if(idx > 10)
                        {
                            cur_bit_rate = (pkt_num - (*pit)->pcr_pkt_list[idx - 10]) * 188 * 8 / 
                                           ((pcr - (*pit)->pcr_list[idx - 10]) / (double)27000);
                            if(cur_bit_rate > 1)
                            {
                                if(cur_bit_rate > max_bit_rate)
                                    max_bit_rate = cur_bit_rate;
                                if(cur_bit_rate < min_bit_rate)
                                    min_bit_rate = cur_bit_rate; 
                            }                             
                        }                                         
                    }
                    (*pit)->pcr_list.Push(pcr);
                    (*pit)->pcr_pkt_list.Push(pkt_num);
                }
            }
        }
    }

    if(adf->discontinuity_indicator)
    {
        raw_ts->discontinuity_flag = true;
    }
    adp_len = 5 + adf->adaptation_field_length;

    delete adf;

    return adp_len;
}

bool TSFactory::continuityCheck(uint8_t* ts_packet, TSData* raw_ts, bool& cc_err)
{
    bool first_flag = false;
    uint8_t expected_counter;

    first_flag = (raw_ts->continuity_counter == TSData::INVALID_CC);
    if(first_flag)
    {
        raw_ts->continuity_counter = ts_packet[3] & 0xf;
    }
    else
    {
        expected_counter = (raw_ts->continuity_counter + 1) & 0xf;
        raw_ts->continuity_counter = ts_packet[3] & 0xf;

        if(expected_counter == ((raw_ts->continuity_counter + 1) & 0xf))
        {
            return false;
        }

        if(expected_counter != raw_ts->continuity_counter)
        {
            raw_ts->Reset();
            cc_err = true;
        }
    }

    return true;
}

void TSFactory::SectionAnalysis(TSData* raw_ts)
{
    Section* sec = NULL;
    try
    {
        sec = createSectoin(raw_ts);
    }
    catch(...)
    {
        raw_ts->Reset();
        throw ;
    }

    if(sec != NULL)
    {
        if(!addSection(sec))
        {
            delete sec;
        }   
    }

    return ;
}

void TSFactory::PESAnalysis(TSData* raw_ts)
{
    raw_ts->getPES();
    if(raw_ts->pes->PTS_DTS_flags & 0x02)
    {
        if(pat == NULL)
            return ;

        std::list<ProgInfo*>::iterator pit = pat->prog_list.begin();
        for(; pit != pat->prog_list.end(); ++pit)
        {
            std::list<Stream*>::iterator sit = (*pit)->stream_list.begin();
            for(; sit != (*pit)->stream_list.end(); ++sit)
            {
                if((*sit)->stream_pid == raw_ts->PID)
                {
                    if(!(*sit)->scrambling)
                    {
                        (*sit)->pts_list.Push(raw_ts->pes->PTS);
                        int idx = (*sit)->pts_list.Size() - 1;
                        if(idx > 0)
                        {
                            int64_t inv= (*sit)->pts_list[idx] - (*sit)->pts_list[idx - 1];
                            double pts_inv = (double)(inv / 90);
                            if(pts_inv > 700 || pts_inv < -700)
                            {
                                std::cout << "pts error!" << std::endl;
                            }
                        }
                        
                        if(raw_ts->pes->PTS_DTS_flags & 0x01)
                        {
                            (*sit)->dts_list.Push(raw_ts->pes->DTS);
                        }
                    }                   
                }
            }
        }
    }
    return ;
}

void TSFactory::TSGather(int pid, uint8_t* ts_packet)
{
    uint8_t* payload_pos = NULL;
    uint8_t available_length;

    bool cc_err = false;
    bool pcr_inv_err = false;
    bool pcr_dis_err = false;
    bool pcr_acu_err = false;

    if(raw_sarr[pid] == NULL)
    {
        raw_sarr[pid] = new TSData(TSData::PESDATA);
        raw_sarr[pid]->PID = pid;
    }

    ++pkt_num;
    ++raw_sarr[pid]->pkt_num;

    if(raw_sarr[pid]->pcr_pid == 0xFFFF)
    {
        if(pat != NULL && !pat->prog_list.empty())
        {
            raw_sarr[pid]->pcr_pid = pat->prog_list.front()->pcr_pid;
        }
    }

    if(pid == 0x1FFF)
    {
        return ;
    }

    TSData* raw_ts = raw_sarr[pid];

    //ts packet start
    if(ts_packet[0] != 0x47)
    {
        return ;
    }

    //section PID
    raw_ts->PID = ((ts_packet[1] & 0x1F) << 8) | ts_packet[2];

    /* Analysis the adaptation_field if present */
    uint8_t adp_ctr = (ts_packet[3] & 0x30) >> 4;
    if(adp_ctr == 0x02 || adp_ctr == 0x03)
        payload_pos = ts_packet + adaptationFieldAnalysis(ts_packet, raw_ts, pcr_inv_err, pcr_dis_err, pcr_acu_err);
    else
        payload_pos = ts_packet + 4;

    /* Continuity check */
    if(!continuityCheck(ts_packet, raw_ts, cc_err))
    {
        return ;
    }

    /* scrambling flag */
    if(ts_packet[3] & 0xC0)
    {
        raw_ts->scrambling_flag = true;
    }

    /* Unit start -> deal the last Section or PES first, then start gather a new one */
    if(ts_packet[1] & 0x40)
    {
        if(raw_ts->type == TSData::SECTION)
        {
            payload_pos = payload_pos + *payload_pos + 1;
            if(raw_ts->recv_length != 0)
            {
                SectionAnalysis(raw_ts);
                raw_ts->Reset();
            } 
            raw_ts->recv_flag = true;
            raw_ts->ts_data_length = (((payload_pos[1] & 0x0F) << 8) | payload_pos[2]) + 3;
        }
        
        if(raw_ts->type == TSData::PESDATA)
        {
            if(raw_ts->recv_length != 0)
            {
                PESAnalysis(raw_ts);
                raw_ts->Reset();
            }
            raw_ts->recv_flag = true;
            raw_ts->ts_data_length = ((payload_pos[4] << 8) | payload_pos[5]) + 6;
            if(raw_ts->ts_data_length == 0)
                raw_ts->ts_data_length = TSData::MAX_TS_LENGTH;
        }
    }

    /* gather the remaining payload into raw_ts */
    if(raw_ts->recv_flag)
    {
        available_length = 188 + ts_packet - payload_pos;
        if(available_length > 0)
        {
            if(raw_ts->type == TSData::PESDATA &&
                raw_ts->recv_length + available_length > raw_ts->ts_data_length)
            {
                raw_ts->ts_data_length += TSData::MAX_TS_LENGTH;
                raw_ts->ts_data = (uint8_t*)realloc(raw_ts->ts_data, raw_ts->ts_data_length);
                raw_ts->pes->raw_data = raw_ts->ts_data;
            }
            memcpy(raw_ts->ts_data + raw_ts->recv_length, payload_pos, available_length);
            raw_ts->recv_length += available_length;
        }
    }

    if(cc_err)
    {
        throw CCErr();
    }
    if(pcr_acu_err)
    {
        throw PcrAcuErr();
    }
    if(pcr_dis_err)
    {
        throw PcrDisErr();
    }
    if(pcr_inv_err)
    {
        throw PcrIntvErr();
    }

    return ;
}

//##ModelId=555550B4016A
Section* TSFactory::createSectoin(TSData* raw_section)
{
    int16_t type = raw_section->PID;
    uint8_t* data = raw_section->ts_data;
    uint32_t len = raw_section->ts_data_length;
    bool srbf = raw_section->scrambling_flag;
    if(type == 0x00)
    {
        if(srbf)
            throw PatErr(PatErr::PSRB);
        raw_section->get_crc();
        return new PAT(data, len, raw_section->crc);
    }
    if(type == 0x01)
    {
        raw_section->get_crc();
        return new CAT(data, len, raw_section->crc);
    }
    if(type == 0x10)
    {
        raw_section->get_crc();
        if(data[0] == 0x40 || data[1] == 0x41) 
            return new NIT(data, len, raw_section->crc);
    }
    if(type == 0x11)
    {
        raw_section->get_crc();
        if(data[0] == 0x4A)
            return new BAT(data, len, raw_section->crc);
        if(data[0] == 0x42 || data[0] == 0x46)
            return new SDT(data, len, raw_section->crc);
    }

    if(type == 0x12)
    {
        raw_section->get_crc();
        if(data[0] == 0x4E || data[0] == 0x4F ||
           (data[0] <= 0x6F && data[0] >= 0x50))
           return new EIT(data, len, raw_section->crc);
    }

    if(type == 0x14)
    {
        if(data[0] == 0x70)
            return new TDT(data, len);
        if(data[0] == 0x73)
        {
            raw_section->get_crc();
            return new TOT(data, len, raw_section->crc);
        }
    }

    if(pat != NULL)
    {
        std::list<ProgInfo*>::iterator pit;
        for(pit = pat->prog_list.begin(); pit != pat->prog_list.end(); ++pit)
        {
            if((*pit)->program_number != 0 && type == (*pit)->program_map_PID)
            {
                if(srbf)
                    throw PmtErr(PmtErr::PSRB);

                raw_section->get_crc();
                return new PMT(data, len, raw_section->crc);
            }
        }
    }

    if(!esg_list.empty())
    {
        std::list<ESGInfo*>::iterator eit;
        for(eit = esg_list.begin(); eit != esg_list.end(); ++eit)
        {
            std::list<uint16_t>::iterator uit;
            for(uit = (*eit)->pid_list.begin(); uit != (*eit)->pid_list.end(); ++uit)
            {
                if(type == *uit)
                {
                    DsmccSection* ds = new DsmccSection(data, len);
                    ds->setBelong(*eit);
                    return ds;
                }
            }
        }
    }
    
    return NULL;
}

//##ModelId=5555977903C2
TSFactory* TSFactory::GetInstance()
{
    if(_instance == NULL)
    {
        _instance = new TSFactory;
    }
    return _instance;
}

//##ModelId=555597630041
TSFactory::TSFactory()
    : pat(NULL),
      pmt_list(),
      nit_list(),
      cat_list(),
      bat_list(),
      sdt_list(),
      eit_list(),
      tdt(NULL),
      tot(NULL),
      esg_list(),
      esg_stable_list(),
      raw_sarr(),
      pkt_num(0),
      max_bit_rate(0),
      min_bit_rate(0),
      cur_bit_rate(0)
{
    int i;
    for(i = 0; i < 0x1F; ++i)
    {
        raw_sarr[i] = new TSData(TSData::SECTION);
    }
}

TSFactory::~TSFactory()
{
    if(pat != NULL)
        delete pat;

    std::set<PMT*, cmp_secp<PMT>>::iterator pit;
    for(pit = pmt_list.begin(); pit != pmt_list.end(); ++pit)
    {
        delete (*pit);
    }
    pmt_list.clear();

    std::set<CAT*, cmp_secp<CAT>>::iterator cit;
    for(cit = cat_list.begin(); cit != cat_list.end(); ++cit)
    {
        delete (*cit);
    }
    cat_list.clear();

    std::set<NIT*, cmp_secp<NIT>>::iterator nit;
    for(nit = nit_list.begin(); nit != nit_list.end(); ++nit)
    {
        delete (*nit);
    }
    nit_list.clear();

    std::list<BAT*>::iterator bit;
    for(bit = bat_list.begin(); bit != bat_list.end(); ++bit)
    {
        delete (*bit);
    }
    bat_list.clear();

    std::set<SDT*, cmp_secp<SDT>>::iterator sit;
    for(sit = sdt_list.begin(); sit != sdt_list.end(); ++sit)
    {
        delete (*sit);
    }
    sdt_list.clear();

    std::set<EIT*, cmp_secp<EIT>>::iterator eit;
    for(eit = eit_list.begin(); eit != eit_list.end(); ++eit)
    {
        delete (*eit);
    }
    eit_list.clear();

    if(tdt != NULL)
        delete tdt;

    if(tot != NULL)
        delete tot;

    std::list<ESGInfo*>::iterator esit;
    for(esit = esg_list.begin(); esit != esg_list.end(); ++esit)
    {
        delete (*esit);
    }
    esg_list.clear();

    for(esit = esg_stable_list.begin(); esit != esg_stable_list.end(); ++esit)
    {
        delete (*esit);
    }
    esg_stable_list.clear();

    for(int i = 0; i < MAX_PID_NUM; ++i)
    {
        if(raw_sarr[i] != NULL)
        {
            delete raw_sarr[i];
            raw_sarr[i] = NULL;
        }
    }

    _instance = NULL;
}

