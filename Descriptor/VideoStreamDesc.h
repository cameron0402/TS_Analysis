#ifndef VIDEOSTREAMDESC_H_HEADER_INCLUDED_AAA7AE26
#define VIDEOSTREAMDESC_H_HEADER_INCLUDED_AAA7AE26
#include "Descriptor.h"

//descriptor_tag = 0x02

//##ModelId=555825B50269
class VideoStreamDesc : public Descriptor
{
  public:
    //##ModelId=55582A460309
    VideoStreamDesc();

    //##ModelId=55582A5201C9
    VideoStreamDesc(uint8_t* data);

    //##ModelId=55582A8C0059
    virtual ~VideoStreamDesc();

    virtual void resolved();

    //##ModelId=5558264C02F7
    bool multiple_frame_rate_flag;
    //##ModelId=5558267C0199
    uint8_t frame_rate_code;
    //##ModelId=555826A20349
    bool MPEG_1_only_flag;
    //##ModelId=555826D701D1
    bool constrained_parameter_flag;
    //##ModelId=5558270501F9
    bool still_picture_flag;
    // used when MPEG_2_flag == 1
    //##ModelId=555827490251
    uint8_t profile_and_level_indication;
    // used when MPEG_2_flag == 1
    //##ModelId=555827D90320
    uint8_t chroma_format;
    // used when MPEG_2_flag == 1
    //##ModelId=555827F10271
    bool frame_rate_extension_flag;
};



#endif /* VIDEOSTREAMDESC_H_HEADER_INCLUDED_AAA7AE26 */
