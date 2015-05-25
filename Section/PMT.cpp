#include "PMT.h"
#include "SectionFactory.h"
#include "../Descriptor/DescFactory.h"
#include "../Descriptor/Descriptor.h"

//##ModelId=55556B720001
PMT::PMT()
{
}

//##ModelId=55556B820369
PMT::PMT(uint8_t* data, uint16_t len)
    : Section(data, len),
      program_number((data[3] << 8) | data[4]), 
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      PCR_PID(((data[8] & 0x1F) << 8) | data[9]),
      program_info_length(((data[10] & 0x0F) << 8) | data[11]),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    int index = 0;
    uint8_t* sub_data = data + 12;
    DescFactory des_fac;
    while(index < program_info_length)
    {
        Descriptor* des = des_fac.createDesc(data[index], data + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }

    index = 12 + program_info_length;
    while(index < len - 4)
    {
        StreamInfo* si = new StreamInfo(data + index);
        index += si->info_length + 5;
        stream_list.push_back(si);
    }
}

//##ModelId=5558288B00A9
PMT::~PMT()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();

    std::list<StreamInfo*>::iterator sit;
    for(sit = stream_list.begin(); sit != stream_list.end(); ++sit)
    {
        delete (*sit);
    }
    stream_list.clear();
}

//##ModelId=555D7D58002F
PMT::StreamInfo::StreamInfo()
{
}

//##ModelId=555D7D6A03E1
PMT::StreamInfo::StreamInfo(uint8_t* data)
    : type(data[0]),
      elem_PID(((data[1] & 0x1F) << 8) | data[2]),
      info_length(((data[3] & 0x0F) << 8) | data[4])    
{
    int index = 0;
    uint8_t* sub_data = data + 5;
    DescFactory des_fac;
    while(index < info_length)
    {
        Descriptor* des = des_fac.createDesc(sub_data[index], sub_data + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }
}

//##ModelId=555D7D6D016C
PMT::StreamInfo::~StreamInfo()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

bool PMT::joinTo(SectionFactory* sf)
{
    std::list<PMT*>::iterator pit;
    for(pit = sf->pmt_list.begin(); pit != sf->pmt_list.end(); ++pit)
    {
        if(*(*pit) == *this)
            return false;
    }
    sf->pmt_list.push_back(this);
    return true;
}

bool PMT::operator==(const PMT& pt)
{
    return crc32 == pt.crc32;
}

