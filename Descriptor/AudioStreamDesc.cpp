#include "AudioStreamDesc.h"

//##ModelId=55582BF20091
AudioStreamDesc::AudioStreamDesc()
{
}

//##ModelId=55582C000312
AudioStreamDesc::AudioStreamDesc(uint8_t* data) 
    : Descriptor(data), 
      free_format_flag(data[2] >> 7),
      ID((data[2] >> 6) & 0x01), 
      layer((data[2] >> 4) & 0x03)                                              
{
}

//##ModelId=55582C65023A
AudioStreamDesc::~AudioStreamDesc()
{
}

