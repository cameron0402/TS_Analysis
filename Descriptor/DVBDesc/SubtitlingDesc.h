#ifndef SUBTITLINGDESC_H_HEADER_INCLUDED_AAA43B1A
#define SUBTITLINGDESC_H_HEADER_INCLUDED_AAA43B1A
#include "../Descriptor.h"

// descriptor_tag = 0x59
//##ModelId=555BEF940100
class SubtitlingDesc : public Descriptor
{
  public:
    //##ModelId=555BEFD602FA
    class SubtitleInfo
    {
      public:
        //##ModelId=555BEFE302D4
        uint8_t ISO6392_language[3];
        //##ModelId=555BF000023D
        uint8_t subtitling_type;
        //##ModelId=555BF01E0287
        uint16_t composition_page_id;
        //##ModelId=555BF0340099
        uint16_t ancillary_page_id;
    };

    //##ModelId=555BF08E02F0
    SubtitlingDesc();

    //##ModelId=555BF097025A
    SubtitlingDesc(uint8_t* data);

    //##ModelId=555BF09F0160
    virtual ~SubtitlingDesc();

    //##ModelId=555BF0620147
    std::list<SubtitleInfo> subtitle_list;
};



#endif /* SUBTITLINGDESC_H_HEADER_INCLUDED_AAA43B1A */
