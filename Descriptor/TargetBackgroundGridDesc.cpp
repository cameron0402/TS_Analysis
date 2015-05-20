#include "TargetBackgroundGridDesc.h"

//##ModelId=555834FD016C
TargetBackgroundGridDesc::TargetBackgroundGridDesc()
{
}

//##ModelId=5558350D030C
TargetBackgroundGridDesc::TargetBackgroundGridDesc(uint8_t* data) 
    : Descriptor(data),
      horizontal_size((data[2] << 6) | (data[3] >> 2)),
      vertical_size(((data[3] & 0x03) << 12) | (data[4] << 4) | (data[5] >> 4)),
      pel_aspect_ratio(data[5] & 0x0F)
{
}

//##ModelId=5558353E0313
TargetBackgroundGridDesc::~TargetBackgroundGridDesc()
{
}

