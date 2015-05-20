#include "ServiceListDesc.h"

//##ModelId=555982E400ED
ServiceListDesc::ServiceListDesc()
{
}

//##ModelId=555982EF00FD
ServiceListDesc::ServiceListDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    ServiceInfo tmp;
    while(index < length + 2)
    {
        tmp.service_id = (data[index] << 8) | data[index + 1];
        tmp.service_type = data[index + 2];
        service_list.push_back(tmp);
        index += 3;
    }
}

//##ModelId=5559831700ED
ServiceListDesc::~ServiceListDesc()
{
}

