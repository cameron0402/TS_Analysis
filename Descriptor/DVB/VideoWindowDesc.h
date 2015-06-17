#ifndef VIDEOWINDOWDESC_H_HEADER_INCLUDED_AAA7C812
#define VIDEOWINDOWDESC_H_HEADER_INCLUDED_AAA7C812
#include "../Descriptor.h"

//descriptor_tag = 0x08

//##ModelId=5558378502C1
class VideoWindowDesc : public Descriptor
{
  public:
    //##ModelId=555839290363
    VideoWindowDesc();

    //##ModelId=555839350384
    VideoWindowDesc(uint8_t* data);

    //##ModelId=5558395C0105
    virtual ~VideoWindowDesc();

    //##ModelId=5558389F02CC
    uint16_t horizontal_offset;
    //##ModelId=555838C9009C
    uint16_t vertical_offset;
    //##ModelId=5558390901B5
    uint8_t window_priority;
};



#endif /* VIDEOWINDOWDESC_H_HEADER_INCLUDED_AAA7C812 */
