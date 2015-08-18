#include "SubtitlingDesc.h"

SubtitlingDesc::SubtitleInfo::SubtitleInfo(uint8_t* data)
    : ISO6392_language(),
      subtitling_type(data[3]),
      composition_page_id((data[4] << 8) | data[5]),
      ancillary_page_id((data[6] << 8) | data[7])
{
    memcpy(ISO6392_language, data, 3);
};

SubtitlingDesc::SubtitleInfo::~SubtitleInfo()
{

}

SubtitlingDesc::SubtitlingDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    SubtitleInfo* tmp;
    while(index < length + 2)
    {
        tmp = new SubtitleInfo(data + index);
        subtitle_list.push_back(tmp);
        index += 8;     
    }
}

SubtitlingDesc::~SubtitlingDesc()
{
    std::list<SubtitlingDesc::SubtitleInfo*>::iterator sit = subtitle_list.begin();
    for(; sit != subtitle_list.end(); ++sit)
        delete (*sit);
}

