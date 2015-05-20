#include "MaximumBitrateDesc.h"

//##ModelId=55594F0D022F
MaximumBitrateDesc::MaximumBitrateDesc()
{
}

//##ModelId=55594F16039F
MaximumBitrateDesc::MaximumBitrateDesc(uint8_t* data) 
    : Descriptor(data),
      maximum_bitrate(((data[2] & 0x3F) << 16) | (data[3] << 8) | data[4])
{
}

//##ModelId=55594F3B0177
MaximumBitrateDesc::~MaximumBitrateDesc()
{
}

