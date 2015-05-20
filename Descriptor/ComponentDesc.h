#ifndef COMPONENTDESC_H_HEADER_INCLUDED_AAA5317F
#define COMPONENTDESC_H_HEADER_INCLUDED_AAA5317F
#include "Descriptor.h"

//descriptor_tag = 0x50
//##ModelId=555ADB390373
class ComponentDesc : public Descriptor
{
  public:
    //##ModelId=555ADBDF0056
    ComponentDesc();

    //##ModelId=555ADBE900B2
    ComponentDesc(uint8_t* data);

    //##ModelId=555ADBFF02F1
    virtual ~ComponentDesc();

    //##ModelId=555ADB650011
    uint8_t stream_content;
    //##ModelId=555ADB7E03C0
    uint8_t component_type;
    //##ModelId=555ADB990178
    uint8_t component_tag;
    //##ModelId=555ADBAE00C1
    uint8_t ISO6392_language[3];
    //##ModelId=555ADBC70309
    uint8_t* text;
};



#endif /* COMPONENTDESC_H_HEADER_INCLUDED_AAA5317F */
