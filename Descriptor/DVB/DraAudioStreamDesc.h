#ifndef _DRA_AUDIO_STREAM_DESC_
#define _DRA_AUDIO_STREAM_DESC_
#include "../Descriptor.h"

//descriptor_tag = 0xa0 conflict with extended_channel_name_descriptor
//used now

class DraAudioStreamDesc : public Descriptor
{
public:
    DraAudioStreamDesc(uint8_t* data);
    virtual ~DraAudioStreamDesc();

    uint8_t sample_rate_index;
    uint8_t num_normal_channels;
    uint8_t num_lfe_channels;
    uint8_t dra_version_flag;
    uint8_t text_present_flag;
    uint8_t language_present_flag;

    uint8_t text_len;
    uint8_t* text;

    uint8_t language[4];
};

#endif