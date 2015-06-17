#ifndef CONTENTDESC_H_HEADER_INCLUDED_AAA56347
#define CONTENTDESC_H_HEADER_INCLUDED_AAA56347
#include "../Descriptor.h"

//descriptor_tag = 0x54
//##ModelId=555AF24E007A
class ContentDesc : public Descriptor
{
  public:
    //##ModelId=555AF25A0195
    class ContentInfo
    {
      public:
        ContentInfo();
        ContentInfo(uint8_t* data);
        virtual ~ContentInfo();
        //##ModelId=555AF27201B5
        uint8_t content_nibble_level_1;
        //##ModelId=555AF294001C
        uint8_t content_nibble_level_2;
        //##ModelId=555AF2AC0196
        uint8_t user_nibble_1;
        //##ModelId=555AF2C90086
        uint8_t user_nibble_2;
    };

    //##ModelId=555AF3270376
    ContentDesc();

    //##ModelId=555AF32E0325
    ContentDesc(uint8_t* data);

    //##ModelId=555AF34201EF
    virtual ~ContentDesc();

    virtual void resolved();

    //##ModelId=555AF2F201E5
    std::list<ContentInfo*> content_list;
};



#endif /* CONTENTDESC_H_HEADER_INCLUDED_AAA56347 */
