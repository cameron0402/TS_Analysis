#include "MultilingualServiceNameDesc.h"

//##ModelId=555C229901ED
MultilingualServiceNameDesc::ServiceInfo::ServiceInfo()
{
}

//##ModelId=555C22A00165
MultilingualServiceNameDesc::ServiceInfo::ServiceInfo(const ServiceInfo& sif)
{
    if(&sif == this)
        return ;
    service_provider_name_length = sif.service_provider_name_length;
    service_provider_name = new uint8_t[service_provider_name_length];
    memcpy(service_provider_name, sif.service_provider_name, service_provider_name_length);

    service_name_length = sif.service_name_length;
    service_name = new uint8_t[service_name_length];
    memcpy(service_name, sif.service_name, service_name_length);
}

//##ModelId=555C22A5032C
MultilingualServiceNameDesc::ServiceInfo::~ServiceInfo()
{
    delete []service_provider_name;
    delete []service_name;
}

//##ModelId=555C22F0024C
MultilingualServiceNameDesc::MultilingualServiceNameDesc()
{
}

//##ModelId=555C22FC0065
MultilingualServiceNameDesc::MultilingualServiceNameDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2; 
    while(index < length + 2)
    {
        ServiceInfo tmp;
        memcpy(tmp.ISO6392_language, data + index, 3);

        tmp.service_provider_name_length = data[index + 4];
        tmp.service_provider_name = new uint8_t[tmp.service_provider_name_length];
        memcpy(tmp.service_provider_name, data + 5 + index, tmp.service_provider_name_length);
        index += 5 + tmp.service_provider_name_length;
        
        tmp.service_name_length = data[index];
        tmp.service_name = new uint8_t[tmp.service_name_length];
        memcpy(tmp.service_name, data + 1 + index, tmp.service_name_length);
        index += 1 + tmp.service_name_length;

        service_list.push_back(tmp);
    }
}

//##ModelId=555C230C0313
MultilingualServiceNameDesc::~MultilingualServiceNameDesc()
{
}

