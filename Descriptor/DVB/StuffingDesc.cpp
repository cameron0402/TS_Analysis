#include "StuffingDesc.h"

//##ModelId=555985150174
StuffingDesc::StuffingDesc()
{
}

//##ModelId=5559851F02A5
StuffingDesc::StuffingDesc(uint8_t* data) : Descriptor(data)
{
    stuffings = new uint8_t[length];
    memcpy(stuffings, data + 2, length);
}

//##ModelId=555985410205
StuffingDesc::~StuffingDesc()
{
    delete []stuffings;
}

