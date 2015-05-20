#include "SmoothingBufferDesc.h"

//##ModelId=555960890314
SmoothingBufferDesc::SmoothingBufferDesc()
{
}

//##ModelId=5559609503B3
SmoothingBufferDesc::SmoothingBufferDesc(uint8_t* data) 
    : Descriptor(data),
      sb_leak_rate(((data[2] & 0x3F) << 16) | (data[3] << 8) | data[4]),
      sb_size(((data[5] & 0x3F) << 16) | (data[6] << 8) | data[7]) 
{
}

//##ModelId=555960B8034B
SmoothingBufferDesc::~SmoothingBufferDesc()
{
}

