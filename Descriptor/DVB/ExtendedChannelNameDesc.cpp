#include "ExtendedChannelNameDesc.h"

ExtendedChannelNameDesc::ExtendedChannelNameDesc(uint8_t* data)
    : Descriptor(data)
{
    extended_channel_name = new uint8_t[length + 1];
    extended_channel_name[length] = 0;
    memcpy(extended_channel_name, data + 2, length);
}

ExtendedChannelNameDesc::~ExtendedChannelNameDesc()
{
    delete []extended_channel_name;
}