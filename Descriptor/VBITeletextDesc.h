#ifndef VBITELETEXTDESC_H_HEADER_INCLUDED_AAA53A0B
#define VBITELETEXTDESC_H_HEADER_INCLUDED_AAA53A0B
#include "Descriptor.h"

//descriptor_tag = 0x46
//##ModelId=5559AEC200F0
class VBITeletextDesc : public Descriptor
{
  public:
    //##ModelId=555A896F028A
    class TeletextInfo
    {
      public:
        //##ModelId=555A897A0112
        uint8_t ISO639_language[3];
        //##ModelId=555A89BA03CE
        uint8_t teletext_type;
        //##ModelId=555A89CD0310
        uint8_t teletext_magazine_number;
        //##ModelId=555A89EA02C3
        uint8_t teletext_page_number;
    };

    //##ModelId=555A8A53013F
    VBITeletextDesc();

    //##ModelId=555A8A6501CF
    VBITeletextDesc(uint8_t* data);

    //##ModelId=555A8A7F0146
    virtual ~VBITeletextDesc();

    //##ModelId=555A8A1403BF
    std::list<TeletextInfo> teletext_list;
};



#endif /* VBITELETEXTDESC_H_HEADER_INCLUDED_AAA53A0B */
