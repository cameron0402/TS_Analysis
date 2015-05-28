#include "EIT.h"
#include "SectionFactory.h"
#include "../Descriptor/Descriptor.h"
#include "../Descriptor/DescFactory.h"

//##ModelId=5563DC4003BF
EIT::EventInfo::EventInfo()
{
}

//##ModelId=5563DC47027B
EIT::EventInfo::EventInfo(uint8_t* data)
    : event_id((data[0] << 8) | data[1]),
      start_time((data[2] << 32) | (data[3] << 24) | (data[4] << 16) | (data[5] << 8) | data[6]),
      duration((data[7] << 16) | (data[8] << 8) | data[9]),
      running_status(data[10] >> 5),
      free_CA_mode((data[10] >> 4) & 0x01),
      descriptors_loop_length(((data[10] & 0x0F) << 8) | data[11])
{
    int idx = 0;
    uint8_t* pd = data + 12;
    DescFactory des_fac;
    while(idx < descriptors_loop_length)
    {
        Descriptor* des = des_fac.createDesc(pd[idx], pd + idx);
        desc_list.push_back(des);
        idx += des->length + 2;
    }
}

//##ModelId=5563DC4D02E1
EIT::EventInfo::~EventInfo()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

//##ModelId=5563DB220128
EIT::EIT()
{
}

//##ModelId=5563DB260334
EIT::EIT(uint8_t* data, uint16_t len)
    : Section(data, len),
      service_id((data[3] << 8) | data[4]), 
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      transport_stream_id((data[8] << 8) | data[9]),
      original_network_id((data[10] << 8) | data[11]),
      segment_last_section_number(data[12]),
      last_table_id(data[13]),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    int index = 14;
    while(index < len - 4)
    {
        EventInfo* ei = new EventInfo(data + index);
        event_list.push_back(ei);
        index += 12 + ei->descriptors_loop_length;
    }
}

//##ModelId=5563DB2B0060
EIT::~EIT()
{
    std::list<EventInfo*>::iterator eit;
    for(eit = event_list.begin(); eit != event_list.end(); ++eit)
    {
        delete (*eit);
    }
    event_list.clear();
}

bool EIT::operator==(const EIT& et)
{
    return crc32 == et.crc32;
}

bool EIT::joinTo(SectionFactory* sf)
{
    std::list<EIT*>::iterator eit;
    for(eit = sf->eit_list.begin(); eit != sf->eit_list.end(); ++eit)
    {
        if(*(*eit) == *this)
            return false;
    }
    sf->eit_list.push_back(this);
    return true;
}

