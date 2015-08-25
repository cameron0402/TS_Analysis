#ifndef SHORTEVENTDESC_H_HEADER_INCLUDED_AAA5730F
#define SHORTEVENTDESC_H_HEADER_INCLUDED_AAA5730F
#include "../Descriptor.h"

// descriptor_tag = 0x4D
class ShortEventDesc : public Descriptor
{
  public:
    ShortEventDesc(uint8_t* data);
    virtual ~ShortEventDesc();

    virtual void resolved();
    char ISO6392_language[4];
    uint8_t event_name_length;
    uint8_t* event_name;
    uint8_t text_length;
    uint8_t* text;
};



#endif /* SHORTEVENTDESC_H_HEADER_INCLUDED_AAA5730F */
