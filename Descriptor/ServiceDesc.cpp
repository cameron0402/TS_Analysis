#include "ServiceDesc.h"

//##ModelId=555A8EC10111
ServiceDesc::ServiceDesc()
{
}

//##ModelId=555A8EC70294
ServiceDesc::ServiceDesc(uint8_t* data)
    : Descriptor(data),
      service_type(data[2]),
      service_provider_length(data[3]),
      service_name_length(data[4 + service_provider_length])
{
    service_provider = new uint8_t[service_provider_length];
    memcpy(service_provider, data + 4, service_provider_length);

    service_name = new uint8_t[service_name_length];
    memcpy(service_name, data + 5 + service_provider_length, service_name_length);

}

//##ModelId=555A8EE702F1
ServiceDesc::~ServiceDesc()
{
    delete []service_name;
    delete []service_provider;
}

