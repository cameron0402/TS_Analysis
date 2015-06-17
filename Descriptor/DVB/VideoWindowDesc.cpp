#include "VideoWindowDesc.h"

//##ModelId=555839290363
VideoWindowDesc::VideoWindowDesc()
{
}

//##ModelId=555839350384
VideoWindowDesc::VideoWindowDesc(uint8_t* data) 
    : Descriptor(data),
      horizontal_offset((data[2] << 6) | (data[3] >> 2)),
      vertical_offset(((data[3] & 0x03) << 12) | (data[4] << 4) | (data[5] >> 4)),
      window_priority(data[5] & 0x0F)
{
}

//##ModelId=5558395C0105
VideoWindowDesc::~VideoWindowDesc()
{
}

