#include "NVODReferenceDesc.h"

//##ModelId=555AA5AF003F
NVODReferenceDesc::NVODReferenceDesc()
{
}

//##ModelId=555AA5BA02C5
NVODReferenceDesc::NVODReferenceDesc(uint8_t* data) : Descriptor(data)
{
    NVODReferInfo tmp;
    int index = 2;
    while(index < length + 2)
    {
        tmp.transport_stream_id = (data[index] << 8) | data[index + 1];
        tmp.original_network_id = (data[index + 2] << 8) | data[index + 3];
        tmp.service_id = (data[index + 4] << 8) | data[index + 5];
        refer_list.push_back(tmp);
        index += 6;
    }
}

//##ModelId=555AA5D2027F
NVODReferenceDesc::~NVODReferenceDesc()
{
}

