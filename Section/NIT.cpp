#include "NIT.h"
#include "SectionFactory.h"
#include "../Descriptor/Descriptor.h"
#include "../Descriptor/DescFactory.h"

//##ModelId=5555875B00F0
NIT::NIT()
{
}

//##ModelId=55558761023E
NIT::NIT(uint8_t* data, uint16_t len)
    : Section(data, len),
      network_id((data[3] << 8) | data[4]), 
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      network_descriptors_length(((data[8] & 0x0F) << 8) | data[9]),
      transport_stream_loop_length(((data[10 + network_descriptors_length] & 0x0F) << 8) | data[11 + network_descriptors_length]),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    int index = 0;
    uint8_t* sub_data = data + 10;
    DescFactory des_fac;
    while(index < network_descriptors_length)
    {
        Descriptor* des = des_fac.createDesc(sub_data[index], sub_data + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }

    index = 0;
    sub_data = data + 12 + network_descriptors_length;
    while(index < transport_stream_loop_length)
    {
        TransStreamInfo* tsi = new TransStreamInfo(data + index);
        index += 4 + tsi->transport_descriptors_length;
        streaminfo_list.push_back(tsi);
    }
}

//##ModelId=555828A60271
NIT::~NIT()
{
    std::list<TransStreamInfo*>::iterator tsit;
    for(tsit = streaminfo_list.begin(); tsit != streaminfo_list.end(); ++tsit)
    {
        delete (*tsit);
    }
    streaminfo_list.clear();

    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

//##ModelId=555D8D48003E
NIT::TransStreamInfo::TransStreamInfo()
{
}

//##ModelId=555D8D580325
NIT::TransStreamInfo::TransStreamInfo(uint8_t* data)
    : transport_stream_id((data[0] << 8) | data[1]),
      original_network_id((data[2] << 8) | data[3]),
      transport_descriptors_length(((data[4] & 0x0F) << 8) | data[5])
{
    int index = 0;
    uint8_t* sub_data = data + 6;
    DescFactory des_fac;
    while(index < transport_descriptors_length)
    {
        Descriptor* des = des_fac.createDesc(sub_data[index], sub_data + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }
}

//##ModelId=555D8D5B00B0
NIT::TransStreamInfo::~TransStreamInfo()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

bool NIT::joinTo(SectionFactory* sf)
{
    std::list<NIT*>::iterator nit;
    for(nit = sf->nit_list.begin(); nit != sf->nit_list.end(); ++nit)
    {
        if(*(*nit) == *this)
            return false;
    }
    sf->nit_list.push_back(this);
    return true;
}

bool NIT::operator ==(const NIT& nt)
{
    return crc32 == nt.crc32;
}

