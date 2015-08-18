#ifndef SUBTITLINGDESC_H_HEADER_INCLUDED_AAA43B1A
#define SUBTITLINGDESC_H_HEADER_INCLUDED_AAA43B1A
#include "../Descriptor.h"

// descriptor_tag = 0x59
class SubtitlingDesc : public Descriptor
{
  public:
    class SubtitleInfo
    {
      public:
        SubtitleInfo(uint8_t* data);
        ~SubtitleInfo();

        uint8_t ISO6392_language[4];
        uint8_t subtitling_type;
        uint16_t composition_page_id;
        uint16_t ancillary_page_id;
    };

    SubtitlingDesc(uint8_t* data);
    virtual ~SubtitlingDesc();

    std::list<SubtitleInfo*> subtitle_list;
};



#endif /* SUBTITLINGDESC_H_HEADER_INCLUDED_AAA43B1A */
