#include "SectionFactory.h"
#include "Section.h"
#include "SectionData.h"
#include "PAT.h"
#include "PMT.h"
#include "CAT.h"
#include "NIT.h"
#include "BAT.h"
#include "SDT.h"
#include "EIT.h"

SectionFactory* SectionFactory::_instance = NULL;

//##ModelId=5555501D00F6
bool SectionFactory::addSection(Section* section)
{
    return section->joinTo(this);
}

void SectionFactory::sectionGather(uint8_t* ts_packet)
{
    uint8_t* payload_pos = NULL;
    bool first_flag = false;
    uint8_t expected_counter;
    uint8_t available_length;

    //ts packet start
    if(ts_packet[0] != 0x47)
        return ;

    //section PID
    raw_section->PID = ((ts_packet[1] & 0x1F) << 8) | ts_packet[2];

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
            std::cout << "PSI decoder TS duplicate (received " << raw_section->continuity_counter 
                      << "expected " << expected_counter
                      << ") for PID " << raw_section->PID << std::endl;
            return ;
        }

        if(expected_counter != raw_section->continuity_counter)
        {
            std::cout << "PSI decoder TS discontinuity (received" << raw_section->continuity_counter 
                      << "expected " << expected_counter
                      << ") for PID " << raw_section->PID << std::endl;
            //section_data->discontinuity_flag = true;
            raw_section->Reset();
        }
    }

    /* Return if no payload in the TS packet */
    if(!(ts_packet[3] & 0x10))
        return ;

    /* Skip the adaptation_field if present */
    if(ts_packet[3] & 0x20)
        payload_pos = ts_packet + 5 + ts_packet[4];
    else
        payload_pos = ts_packet + 4;

    /* Unit start -> skip the pointer_field and a new section begins */
    if(ts_packet[1] & 0x40)
    {
        payload_pos = payload_pos + *payload_pos + 1;
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
            raw_section->section_data_length = ((payload_pos[1] & 0x1F) << 8) | payload_pos[2] + 3;
            if(raw_section->section_data_length > SectionData::MAX_SECTION_LENGTH)
            {
                std::cout << "PSI decoder PSI section too long" << std::endl;
                raw_section->Reset();
                available_length = 0;
            }
            payload_pos += 3;
            available_length -= 3;
        }
        // recv the last ts_packet
        else if(available_length >= remain_length)
        {
            memcpy(raw_section->section_data + raw_section->recv_length, payload_pos, remain_length);
            payload_pos += remain_length;
            available_length -= remain_length;
            raw_section->recv_length += remain_length;

            Section* sec = createSectoin(raw_section);
            if(!addSection(sec))
                delete sec;
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

    return ;
}

//##ModelId=555550B4016A
Section* SectionFactory::createSectoin(SectionData* raw_section)
{
    int16_t type = raw_section->PID;
    uint8_t* data = raw_section->section_data;
    uint16_t len = raw_section->section_data_length;
    if(type == 0x00)
    {
        return new PAT(data, len);
    }
    if(type == 0x01)
    {
        return new CAT(data, len);
    }
    if(type == 0x10)
    {
        if(data[0] == 0x40 || data[1] == 0x41) 
            return new NIT(data, len);
    }
    if(type == 0x11)
    {
        if(data[0] == 0x4A)
            return new BAT(data, len);
        if(data[0] == 0x42 || data[0] == 0x46)
            return new SDT(data, len);
    }

    if(type == 0x12)
    {
        if(data[0] == 0x4E || data[0] == 0x4F ||
           (data[0] <= 0x6F && data[0] >= 0x50))
           return new EIT(data, len);
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
      pmt_list(0),
      nit_list(0),
      cat_list(0),
      bat_list(0),
      sdt_list(0),
      eit_list(0),
      raw_section(new SectionData())
{
}

SectionFactory::~SectionFactory()
{
    if(pat != NULL)
        delete pat;

    std::list<PMT*>::iterator pit;
    for(pit = pmt_list.begin(); pit != pmt_list.end(); ++pit)
    {
        delete (*pit);
    }
    pmt_list.clear();

    std::list<CAT*>::iterator cit;
    for(cit = cat_list.begin(); cit != cat_list.end(); ++cit)
    {
        delete (*cit);
    }
    cat_list.clear();

    std::list<NIT*>::iterator nit;
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

    std::list<SDT*>::iterator sit;
    for(sit = sdt_list.begin(); sit != sdt_list.end(); ++sit)
    {
        delete (*sit);
    }
    sdt_list.clear();

    std::list<EIT*>::iterator eit;
    for(eit = eit_list.begin(); eit != eit_list.end(); ++eit)
    {
        delete (*eit);
    }
    eit_list.clear();

    delete raw_section;
}

