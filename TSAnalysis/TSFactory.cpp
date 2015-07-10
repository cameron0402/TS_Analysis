#include "TSFactory.h"
#include "TSData.h"
#include "PES/AdaptationField.h"

TSFactory* TSFactory::_instance = NULL;

//##ModelId=5555501D00F6
bool TSFactory::addSection(Section* section)
{
    return section->joinTo(this);
}

void TSFactory::TSGather(int pid, uint8_t* ts_packet)
{
    uint8_t* payload_pos = NULL;
    uint8_t* p_new_pos = NULL;
    bool first_flag = false;
    uint8_t expected_counter;
    uint8_t available_length;
    uint8_t adp_ctr = 0;

    bool cc_err = false;
    bool pcr_inv_err = false;
    bool pcr_dis_err = false;
    bool pcr_acu_err = false;

    ++pkt_idx;

    if(raw_sarr[pid] == NULL)
    {
        raw_sarr[pid] = new TSData(TSData::PES);
    }

    if(pid == 0x1FFF)
    {
        return ;
    }

    TSData* raw_ts = raw_sarr[pid];

    //ts packet start
    if(ts_packet[0] != 0x47)
        return ;

    //section PID
    raw_ts->PID = pid;//((ts_packet[1] & 0x1F) << 8) | ts_packet[2];

    /* Analysis the adaptation_field if present */
    adp_ctr = (ts_packet[3] & 0x30) >> 4;
    if(adp_ctr == 0x02 || adp_ctr == 0x03)
    {
        AdaptationField* adf = new AdaptationField(ts_packet + 4);

        if(adf->PCR_flag)
        {
            uint64_t pcr = adf->program_clock_reference_base * 300 + adf->program_clock_reference_extension;
            std::list<PCR*>::iterator pit = pcr_list.begin();
            for(; pit != pcr_list.end(); ++pit)
            {
                if((*pit)->pid == pid)
                    break;
            }

            if(pit == pcr_list.end())
            {
                PCR* p = new PCR(pid, 1000);
                p->st_pkt_idx = pkt_idx;
                p->push_pcr(pcr);
                pcr_list.push_back(p);
            }
            else
            {
                int64_t pcr_pre = (*pit)->time_list.back();
                int64_t pcr_intv = pcr - pcr_pre;

                uint32_t pkt_num_pre, pkt_num;
                int64_t pcr_intv_pre, pcr_intv_exp;

                double inv = double(pcr_intv) / 27000;
                (*pit)->push_pcr(pcr);
                if((*pit)->ed_pkt_idx == 0)
                {
                    (*pit)->ed_pkt_idx = pkt_idx;
                    (*pit)->intv = pcr_intv;
                }
                else
                {
                    pkt_num_pre = (*pit)->ed_pkt_idx - (*pit)->st_pkt_idx;
                    pcr_intv_pre = (*pit)->intv;

                    pkt_num = pkt_idx - (*pit)->ed_pkt_idx;
                    pcr_intv_exp = pcr_intv_pre * pkt_num / pkt_num_pre;

                    (*pit)->st_pkt_idx = (*pit)->ed_pkt_idx;
                    (*pit)->ed_pkt_idx = pkt_idx;
                    (*pit)->intv = pcr_intv;

                    if(pcr_intv_exp - pcr_intv > 14 || pcr_intv_exp - pcr_intv < -14)
                    {
                        pcr_acu_err = true;
                    }
                }
                
                if(inv > 100 && !adf->discontinuity_indicator)
                {
                    pcr_dis_err = true;
                }

                if(inv > 40)
                {
                    pcr_inv_err = true;
                }
            }
           
        }

        if(adf->discontinuity_indicator)
        {
            raw_ts->discontinuity_flag = true;
        }

        payload_pos = ts_packet + 5 + adf->adaptation_field_length;

        delete adf;
    }
    else
    {
        payload_pos = ts_packet + 4;
    }

    /* Continuity check */
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
            if(adp_ctr == 0x02)
            {
                return ;
            }
            else if(!raw_ts->discontinuity_flag)
            {
                std::cout << "PSI decoder TS duplicate (received " << (int)raw_ts->continuity_counter
                    << " expected " << (int)expected_counter 
                    << ") for PID " << raw_ts->PID << std::endl;
                raw_ts->Reset();
                return ;
            } 
        }

        if(expected_counter != raw_ts->continuity_counter)
        {
            raw_ts->Reset();
            cc_err = true;
        }
    }

    /* Return if no payload in the TS packet */
    if(!(ts_packet[3] & 0x10))
        return ;

    /* Unit start -> skip the pointer_field and a new section begins */
    if(ts_packet[1] & 0x40)
    {
        p_new_pos = payload_pos + *payload_pos + 1;
        payload_pos += 1;
    }

    if(raw_ts->recv_length == 0)
    {
        if(p_new_pos != NULL)
        {
            payload_pos = p_new_pos;
            p_new_pos = NULL;
        }
        else
        {
            return ;
        }
    }

    /* Remaining bytes in the payload */
    available_length = 188 + ts_packet - payload_pos;
    while(available_length > 0)
    {
        uint16_t remain_length = raw_ts->ts_data_length - raw_ts->recv_length;
        // recv the section_data header
        if(raw_ts->recv_length == 0)
        {
            memcpy(raw_ts->ts_data, payload_pos, 3);
            raw_ts->recv_length += 3;
            raw_ts->ts_data_length = (((payload_pos[1] & 0x0F) << 8) | payload_pos[2]) + 3;
            if(raw_ts->ts_data_length > TSData::MAX_TS_LENGTH)
            {
                std::cout << "PSI decoder PSI section too long" << std::endl;
                raw_ts->Reset();
                available_length = 0;
                break;
            }
            payload_pos += 3;
            available_length -= 3;
        }
        // recv the last ts_packet
        else if(available_length >= remain_length)
        {
            Section* sec = NULL;
            memcpy(raw_ts->ts_data + raw_ts->recv_length, payload_pos, remain_length);
            payload_pos += remain_length;
            available_length -= remain_length;
            raw_ts->recv_length += remain_length;

            if(raw_ts->type == TSData::SECTION) // deal section
            {
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
            }
            else // deal pes
            {

            }
              
            raw_ts->Reset();
            
            /* A TS packet may contain any number of sections, only the first
             * new one is flagged by the pointer_field. If the next payload
             * byte isn't 0xff then a new section starts. */
            if(*payload_pos == 0xff)
                available_length = 0;
        }
        // recv ts_packet
        else
        {
            memcpy(raw_ts->ts_data + raw_ts->recv_length, payload_pos, available_length);
            raw_ts->recv_length += available_length;
            available_length = 0;
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
    uint16_t len = raw_section->ts_data_length;
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
        std::list<PAT::ProgInfo*>::iterator pit;
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
      pcr_list(),
      pkt_idx(0)
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

    std::list<PCR*>::iterator pcit = pcr_list.begin();
    for(; pcit != pcr_list.end(); ++pcit)
    {
        delete (*pcit);
    }
    pcr_list.clear();
}

