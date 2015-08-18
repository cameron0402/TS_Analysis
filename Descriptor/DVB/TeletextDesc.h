#ifndef TELETEXTDESC_H_HEADER_INCLUDED_AAA508B2
#define TELETEXTDESC_H_HEADER_INCLUDED_AAA508B2
#include "../Descriptor.h"

//descriptor_tag = 0x56
class TeletextDesc : public Descriptor
{
  public:
    class TextInfo
    {
      public:
        TextInfo(uint8_t* data);
        ~TextInfo();

        uint8_t ISO6392_language[4];
        uint8_t teletext_type;
        uint8_t teletext_magazine_number;
        uint8_t teletext_page_number;
    };

    TeletextDesc(uint8_t* data);
    virtual ~TeletextDesc();

    std::list<TextInfo*> text_list;
};

#endif /* TELETEXTDESC_H_HEADER_INCLUDED_AAA508B2 */
