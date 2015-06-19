#include "SectionFactory.h"
#include "SectionData.h"

SectionFactory* SectionFactory::_instance = NULL;

//##ModelId=5555501D00F6
bool SectionFactory::addSection(Section* section)
{
    return section->joinTo(this);
}

void SectionFactory::sectionGather(int pid, uint8_t* ts_packet)
{
    uint8_t* payload_pos = NULL;
    uint8_t* p_new_pos = NULL;
    bool first_flag = false;
    uint8_t expected_counter;
    uint8_t available_length;
    bool cc_err_f = false;

    if(raw_sarr[pid] == NULL)
    {
        return ;
        //raw_sarr[pid] = new SectionData();
    }

    SectionData* raw_section = raw_sarr[pid];

    //ts packet start
    if(ts_packet[0] != 0x47)
        return ;

    //section PID
    raw_section->PID = pid;//((ts_packet[1] & 0x1F) << 8) | ts_packet[2];

    /* Continuity check */
    first_flag = (raw_section->continuity_counter == SectionData::INVALID_CC);
    if(first_flag)
    {
        raw_section->continuity_counter = ts_packet[3] & 0xf;
    }
    else
    {
        expected_counter = (raw_section->continuity_counter + 1) & 0xf;
        raw_section->continuity_counter = ts_packet[3] & 0xf;

        if(expected_counter == ((raw_section->continuity_counter + 1) & 0xf) && 
           !raw_section->discontinuity_flag)
        {
            std::cout << "PSI decoder TS duplicate (received " << (int)raw_section->continuity_counter
                      << " expected " << (int)expected_counter 
                      << ") for PID " << raw_section->PID << std::endl;
            return ;
        }

        if(expected_counter != raw_section->continuity_counter)
        {
            raw_section->Reset();
            cc_err_f = true;
        }
    }

    /* Return if no payload in the TS packet */
    if(!(ts_packet[3] & 0x10))
        return ;

    /* Scrambling flag */
    raw_section->scrambling_flag = ts_packet[3] >> 6;
    if(raw_section->scrambling_flag && cat_list.empty())
    {
        raw_section->Reset();
        throw CatErr(CatErr::CSRB);
    }

    /* Skip the adaptation_field if present */
    if(ts_packet[3] & 0x20)
        payload_pos = ts_packet + 5 + ts_packet[4];
    else
        payload_pos = ts_packet + 4;

    /* Unit start -> skip the pointer_field and a new section begins */
    if(ts_packet[1] & 0x40)
    {
        p_new_pos = payload_pos + *payload_pos + 1;
        payload_pos += 1;
    }

    if(raw_section->recv_length == 0)
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
        uint16_t remain_length = raw_section->section_data_length - raw_section->recv_length;
        // recv the section_data header
        if(raw_section->recv_length == 0)
        {
            memcpy(raw_section->section_data, payload_pos, 3);
            raw_section->recv_length += 3;
            raw_section->section_data_length = (((payload_pos[1] & 0x0F) << 8) | payload_pos[2]) + 3;
            if(raw_section->section_data_length > SectionData::MAX_SECTION_LENGTH)
            {
                std::cout << "PSI decoder PSI section too long" << std::endl;
                raw_section->Reset();
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
            memcpy(raw_section->section_data + raw_section->recv_length, payload_pos, remain_length);
            payload_pos += remain_length;
            available_length -= remain_length;
            raw_section->recv_length += remain_length;

            raw_section->get_crc();

            try
            {
                sec = createSectoin(raw_section);
            }
            catch(...)
            {
                raw_section->Reset();
                throw ;
            }
            
            if(sec != NULL)
            {
                if(!addSection(sec))
                {
                    delete sec;
                }   
            }
            
            raw_section->Reset();
            
            /* A TS packet may contain any number of sections, only the first
             * new one is flagged by the pointer_field. If the next payload
             * byte isn't 0xff then a new section starts. */
            if(*payload_pos == 0xff)
                available_length = 0;
        }
        // recv ts_packet
        else
        {
            memcpy(raw_section->section_data + raw_section->recv_length, payload_pos, available_length);
            raw_section->recv_length += available_length;
            available_length = 0;
        }
    }

    if(cc_err_f)
    {
        throw CCErr();
    }

    return ;
}

//##ModelId=555550B4016A
Section* SectionFactory::createSectoin(SectionData* raw_section)
{
    int16_t type = raw_section->PID;
    uint8_t* data = raw_section->section_data;
    uint16_t len = raw_section->section_data_length;
    bool srbf = raw_section->scrambling_flag;
    uint32_t crc = raw_section->crc;
    if(type == 0x00)
    {
        if(srbf)
            throw PatErr(PatErr::PSRB);

        return new PAT(data, len, crc);
    }
    if(type == 0x01)
    {
        return new CAT(data, len, crc);
    }
    if(type == 0x10)
    {
        if(data[0] == 0x40 || data[1] == 0x41) 
            return new NIT(data, len, crc);
    }
    if(type == 0x11)
    {
        if(data[0] == 0x4A)
            return new BAT(data, len, crc);
        if(data[0] == 0x42 || data[0] == 0x46)
            return new SDT(data, len, crc);
    }

    if(type == 0x12)
    {
        if(data[0] == 0x4E || data[0] == 0x4F ||
           (data[0] <= 0x6F && data[0] >= 0x50))
           return new EIT(data, len, crc);
    }

    if(type == 0x14)
    {
        if(data[0] == 0x70)
            return new TDT(data, len);
        if(data[0] == 0x73)
            return new TOT(data, len, crc);
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

                return new PMT(data, len, crc);
            }
        }
    }
    
    return NULL;
}

//##ModelId=5555977903C2
SectionFactory* SectionFactory::GetInstance()
{
    if(_instance == NULL)
    {
        _instance = new SectionFactory;
    }
    return _instance;
}

//##ModelId=555597630041
SectionFactory::SectionFactory()
    : pat(NULL),
      pmt_list(),
      nit_list(),
      cat_list(),
      bat_list(),
      sdt_list(),
      eit_list(),
      tdt(NULL),
      tot(NULL),
      raw_sarr()
{
    int i;
    for(i = 0; i < 0x1F; ++i)
    {
        raw_sarr[i] = new SectionData();
    }
}

SectionFactory::~SectionFactory()
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

    for(int i = 0; i < MAX_PID_NUM; ++i)
    {
        if(raw_sarr[i] != NULL)
        {
            delete raw_sarr[i];
            raw_sarr[i] = NULL;
        }
    }
}

