#ifndef AUDIOSTREAMDESC_H_HEADER_INCLUDED_AAA7B018
#define AUDIOSTREAMDESC_H_HEADER_INCLUDED_AAA7B018
#include "../Descriptor.h"

//descriptor_tag = 0x03
class AudioStreamDesc : public Descriptor
{
  public:
    AudioStreamDesc();
    AudioStreamDesc(uint8_t* data);
    virtual ~AudioStreamDesc();

    virtual void resolved();

    bool free_format_flag;
    uint8_t ID;
    uint8_t layer;

    bool variable_rate_audio_indicator;
};



#endif /* AUDIOSTREAMDESC_H_HEADER_INCLUDED_AAA7B018 */
