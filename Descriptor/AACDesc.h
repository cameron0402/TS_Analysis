#ifndef AACDESC_H_HEADER_INCLUDED_AAA2D9A8
#define AACDESC_H_HEADER_INCLUDED_AAA2D9A8
#include "Descriptor.h"

//descriptor_tag = 0x7C
//##ModelId=555D486D025D
class AACDesc : public Descriptor
{
  public:
    //##ModelId=555D487E0062
    AACDesc();

    //##ModelId=555D48800042
    AACDesc(uint8_t* data);

    //##ModelId=555D4881039A
    virtual ~AACDesc();

    //##ModelId=555D48BB03D0
    uint8_t profile_and_level;
    //##ModelId=555D48D500DE
    uint8_t AAC_type_flag;
    //##ModelId=555D48EA0321
    uint8_t AAC_type;
    //##ModelId=555D48FE0248
    uint8_t* add_info;
};



#endif /* AACDESC_H_HEADER_INCLUDED_AAA2D9A8 */
