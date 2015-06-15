#include "SubtitlingDesc.h"

//##ModelId=555BF08E02F0
SubtitlingDesc::SubtitlingDesc()
{
}

//##ModelId=555BF097025A
SubtitlingDesc::SubtitlingDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    SubtitleInfo tmp;
    while(index < length + 2)
    {
        memcpy(tmp.ISO6392_language, data + index, 3);
        tmp.subtitling_type = data[index + 4];
        tmp.composition_page_id = (data[index + 5] << 8) | data[index + 6];
        tmp.ancillary_page_id = (data[index + 7] << 8) | data[index + 8];
        index += 8;

        subtitle_list.push_back(tmp);
    }
}

//##ModelId=555BF09F0160
SubtitlingDesc::~SubtitlingDesc()
{
}

