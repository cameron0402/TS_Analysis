#include "DTSAudioStreamDesc.h"

//##ModelId=555D43EF01FD
DTSAudioStreamDesc::DTSAudioStreamDesc()
{
}

//##ModelId=555D43F101BB
DTSAudioStreamDesc::DTSAudioStreamDesc(uint8_t* data)
    : Descriptor(data),
      sample_rate_code(data[2] >> 4),
      bit_rate_code(((data[2] & 0xF) << 2) | (data[2] >> 6)),
      nblks(((data[2] & 0x3F) << 1) | (data[3] >> 7)),
      fsize(((data[3] & 0x7F) << 7) | (data[4] >> 1)),
      surround_mode(((data[4] & 0x01) << 5) | data[5] >> 3),
      ife_flag((data[5] >> 2) & 0x01),
      extended_surround_flag(data[5] & 0x03)
{
    add_info = new uint8_t[length - 4];
    memcpy(add_info, data + 6, length - 4);
}

//##ModelId=555D43F3012C
DTSAudioStreamDesc::~DTSAudioStreamDesc()
{
    delete []add_info;
}

