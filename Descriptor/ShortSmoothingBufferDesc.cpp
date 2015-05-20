#include "ShortSmoothingBufferDesc.h"

//##ModelId=555C364D01D9
ShortSmoothingBufferDesc::ShortSmoothingBufferDesc()
{
}

//##ModelId=555C365001B6
ShortSmoothingBufferDesc::ShortSmoothingBufferDesc(uint8_t* data)
    : Descriptor(data),
      sb_size(data[2] >> 6),
      sb_lead_rate(data[2] & 0x3F)
{
}

//##ModelId=555C36530040
ShortSmoothingBufferDesc::~ShortSmoothingBufferDesc()
{
}

