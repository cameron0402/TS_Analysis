#include "IBPDesc.h"

//##ModelId=5559779B017B
IBPDesc::IBPDesc()
{
}

//##ModelId=555977A00190
IBPDesc::IBPDesc(uint8_t* data) 
    : Descriptor(data),
      closed_gop_flag(data[2] >> 7),
      identical_gop_flag((data[2] >> 6) & 0x01),
      max_gop_length(((data[2] & 0x3F) << 8) | data[3])
{
}

//##ModelId=555977CA0358
IBPDesc::~IBPDesc()
{
}

