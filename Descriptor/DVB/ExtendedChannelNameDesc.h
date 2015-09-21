#ifndef _EXTENDED_CHANNEL_NAME_DESC_
#define _EXTENDED_CHANNEL_NAME_DESC_

#include "../Descriptor.h"

//descriptor_tag = 0xa0 but conflict with dra_audio_stream_descriptor 
//not used now
class ExtendedChannelNameDesc : public Descriptor
{
public:
    ExtendedChannelNameDesc(uint8_t* data);
    virtual ~ExtendedChannelNameDesc();

    uint8_t* extended_channel_name;
};

#endif