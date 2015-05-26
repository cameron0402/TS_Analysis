#include "SDT.h"
#include "SectionFactory.h"
#include "../Descriptor/Descriptor.h"
#include "../Descriptor/DescFactory.h"

//##ModelId=5563CDBD00BF
SDT::SDT()
{
}

//##ModelId=5563CDCB02BF
SDT::SDT(uint8_t* data, uint16_t len)
    : Section(data, len),
      transport_stream_id((data[3] << 8) | data[4]), 
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      original_network_id((data[8] << 8) | data[9]),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    int index = 10;
    while(index < len - 4)
    {
        ServiceInfo* si = new ServiceInfo(data + index);
        service_list.push_back(si);
        index += 5 + si->descriptors_loop_length;
    }
}

//##ModelId=5563CE0800BB
SDT::~SDT()
{
    std::list<ServiceInfo*>::iterator sit;
    for(sit = service_list.begin(); sit != service_list.end(); ++sit)
    {
        delete (*sit);
    }
    service_list.clear();
}

//##ModelId=5563D0B20194
SDT::ServiceInfo::ServiceInfo()
{
}

//##ModelId=5563D0B900DD
SDT::ServiceInfo::ServiceInfo(uint8_t* data)
    : service_id((data[0] << 8) | data[1]),
      EIT_schedule_flag((data[2] >> 1) & 0x01),
      EIT_present_following_flag(data[2] & 0x01),
      running_status(data[3] >> 5),
      free_CA_mode((data[3] >> 4) & 0x01),
      descriptors_loop_length(((data[3] & 0x0F) << 8) | data[4])
{
    int idx = 0;
    DescFactory des_fac;
    uint8_t* pd = data + 5;
    while(idx < descriptors_loop_length)
    {
        Descriptor* des = des_fac.createDesc(data[idx], data + idx);
        desc_list.push_back(des);
        idx += des->length + 2;
    }
}

//##ModelId=5563D0D1019A
SDT::ServiceInfo::~ServiceInfo()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

bool SDT::operator==(const SDT& st)
{
    return crc32 == st.crc32;
}

bool SDT::joinTo(SectionFactory* sf)
{
    std::list<SDT*>::iterator sit;
    for(sit = sf->sdt_list.begin(); sit != sf->sdt_list.end(); ++sit)
    {
        if(*(*sit) == *this)
            return false;
    }
    sf->sdt_list.push_back(this);
    return true;
}

