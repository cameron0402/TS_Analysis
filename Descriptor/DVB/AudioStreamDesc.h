#ifndef AUDIOSTREAMDESC_H_HEADER_INCLUDED_AAA7B018
#define AUDIOSTREAMDESC_H_HEADER_INCLUDED_AAA7B018
#include "../Descriptor.h"

//descriptor_tag = 0x03

//##ModelId=55582B600234
class AudioStreamDesc : public Descriptor
{
  public:
    //##ModelId=55582BF20091
    AudioStreamDesc();

    //##ModelId=55582C000312
    AudioStreamDesc(uint8_t* data);

    //##ModelId=55582C65023A
    virtual ~AudioStreamDesc();

    virtual void resolved();

    //##ModelId=55582B7800F3
    bool free_format_flag;
    //##ModelId=55582BB0007A
    uint8_t ID;
    //##ModelId=55582BC70242
    uint8_t layer;

    bool variable_rate_audio_indicator;
};



#endif /* AUDIOSTREAMDESC_H_HEADER_INCLUDED_AAA7B018 */
