#ifndef SHORTEVENTDESC_H_HEADER_INCLUDED_AAA5730F
#define SHORTEVENTDESC_H_HEADER_INCLUDED_AAA5730F
#include "Descriptor.h"

// descriptor_tag = 0x4D
//##ModelId=555AAABE03A6
class ShortEventDesc : public Descriptor
{
  public:
    //##ModelId=555AABE400CA
    ShortEventDesc();

    //##ModelId=555AABF40041
    ShortEventDesc(uint8_t* data);

    //##ModelId=555AAC0C03A9
    virtual ~ShortEventDesc();

    virtual void resolved();

    //##ModelId=555AAB460181
    char ISO6392_language[3];
    //##ModelId=555AAB9701A1
    uint8_t event_name_length;
    //##ModelId=555AABB203B8
    uint8_t* event_name;
    //##ModelId=555AABC203C9
    uint8_t text_length;
    //##ModelId=555AABD2013A
    uint8_t* text;
};



#endif /* SHORTEVENTDESC_H_HEADER_INCLUDED_AAA5730F */
