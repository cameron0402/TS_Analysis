#include "PartialTransportStreamDesc.h"

//##ModelId=555C3A740160
PartialTransportStreamDesc::PartialTransportStreamDesc()
{
}

//##ModelId=555C3A7602E9
PartialTransportStreamDesc::PartialTransportStreamDesc(uint8_t* data)
    : Descriptor(data), 
      peak_rate(((data[2] & 0x3F) << 16) | (data[3] << 8) | data[4]),
      minimum_overall_smoothing_rate(((data[5] & 0x3F) << 16) | (data[6] << 8) | data[7]),
      maximum_overall_smoothing_butter(((data[8] & 0x3F) << 8) | data[9])
{
}

//##ModelId=555C3A780302
PartialTransportStreamDesc::~PartialTransportStreamDesc()
{
}

