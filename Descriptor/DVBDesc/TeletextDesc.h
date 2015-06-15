#ifndef TELETEXTDESC_H_HEADER_INCLUDED_AAA508B2
#define TELETEXTDESC_H_HEADER_INCLUDED_AAA508B2
#include "../Descriptor.h"

//descriptor_tag = 0x56
//##ModelId=555AFCD400C2
class TeletextDesc : public Descriptor
{
  public:
    //##ModelId=555AFCE90008
    class TextInfo
    {
      public:
        //##ModelId=555AFD03029F
        uint8_t ISO6392_language[3];
        //##ModelId=555AFD0E00F0
        uint8_t teletext_type;
        //##ModelId=555AFD3E02B0
        uint8_t teletext_magazine_number;
        //##ModelId=555AFD4A0267
        uint8_t teletext_page_number;
    };

    //##ModelId=555AFD7F01E8
    TeletextDesc();

    //##ModelId=555AFD880150
    TeletextDesc(uint8_t* data);

    //##ModelId=555AFD9B0148
    virtual ~TeletextDesc();

    //##ModelId=555AFD6403CF
    std::list<TextInfo> text_list;
};



#endif /* TELETEXTDESC_H_HEADER_INCLUDED_AAA508B2 */
