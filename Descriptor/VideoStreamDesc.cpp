#include "VideoStreamDesc.h"

//##ModelId=55582A460309
VideoStreamDesc::VideoStreamDesc()
{
}

//##ModelId=55582A5201C9
VideoStreamDesc::VideoStreamDesc(uint8_t* data) 
    : Descriptor(data),
      multiple_frame_rate_flag(data[2] >> 7),
      frame_rate_code((data[2] >> 3) & 0x0F),
      MPEG_2_flag((data[2] >> 2) & 0x01),
      constrained_parameter_flag((data[2] >> 1) & 0x01),
      still_picture_flag(data[2] & 0x01)
{
    if(MPEG_2_flag)
    {
        profile_and_level_indication = data[3];
        chroma_format = data[4] >> 6;
        frame_rate_extension_flag = (data[4] >> 5) & 0x01;
    }
}

//##ModelId=55582A8C0059
VideoStreamDesc::~VideoStreamDesc()
{
}

