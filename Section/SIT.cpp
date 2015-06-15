#include "SIT.h"
#include "../Descriptor/Descriptor.h"
#include "../Descriptor/DVBDesc/DescFactory.h"

//##ModelId=556429E100BC
SIT::ServiceInfo::ServiceInfo()
{
}

//##ModelId=556429E800A8
SIT::ServiceInfo::ServiceInfo(uint8_t* data)
    : service_id((data[0] << 8) | data[1]),
      running_status((data[2] >> 4) & 0x07),
      service_loop_length(((data[2] & 0x0F) << 8) | data[3])
{
    int index = 0;
    uint8_t* pd = data + 4;
    DescFactory des_fac;
    while(index < service_loop_length)
    {
        Descriptor* des = des_fac.createDesc(pd[index], pd + index);
        desc_list.push_back(des);
        index += des->length + 2;
    }
}

//##ModelId=556429EE0080
SIT::ServiceInfo::~ServiceInfo()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

//##ModelId=556428CC02B1
SIT::SIT()
{
}

//##ModelId=556428CF03E6
SIT::SIT(uint8_t* data, uint16_t len, uint32_t crc)
    : Section(data, len),
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      transmission_info_loop_length(((data[8] & 0x0F) << 8) | data[9]),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    int idx = 0;
    uint8_t* pd = data + 10;
    DescFactory des_fac;
    while(idx < transmission_info_loop_length)
    {
        Descriptor* des = des_fac.createDesc(pd[idx], pd + idx);
        desc_list.push_back(des);
        idx += des->length + 2;
    }

    idx = 10 + transmission_info_loop_length;
    while(idx < len - 4)
    {
        ServiceInfo* si = new ServiceInfo(data + idx);
        service_list.push_front(si);
        idx += si->service_loop_length + 4;
    }
}

//##ModelId=556428D30298
SIT::~SIT()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();

    std::list<ServiceInfo*>::iterator sit;
    for(sit = service_list.begin(); sit != service_list.end(); ++sit)
    {
        delete (*sit);
    }
    service_list.clear();

}

