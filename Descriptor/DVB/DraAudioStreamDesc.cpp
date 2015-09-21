#include "DraAudioStreamDesc.h"

DraAudioStreamDesc::DraAudioStreamDesc(uint8_t* data)
    : Descriptor(data),
      sample_rate_index(data[2] >> 4),
      num_normal_channels(((data[2] & 0xF) << 2) | (data[3] >> 6)),
      num_lfe_channels((data[3] >> 4) & 0x3),
      dra_version_flag((data[3] >> 3) & 0x1),
      text_present_flag((data[3] >> 2) & 0x1),
      language_present_flag((data[3] >> 1) & 0x1),
      text_len(0),
      text(NULL),
      language()
{
    int idx = 4;
    if(text_present_flag)
    {
        text_len = data[idx++];
        text = new uint8_t[text_len + 1];
        text[text_len] = 0;
        memcpy(text, data + idx, text_len);
        idx += text_len;
    }

    if(language_present_flag)
    {
        memcpy(language, data + idx, 3);
    }
}

DraAudioStreamDesc::~DraAudioStreamDesc()
{
    if(text != NULL)
    {
        delete []text;
    }
}