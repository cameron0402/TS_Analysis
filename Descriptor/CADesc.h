#ifndef CADESC_H_HEADER_INCLUDED_AAA79354
#define CADESC_H_HEADER_INCLUDED_AAA79354
#include "Descriptor.h"

//descriptor_tag = 0x09

//##ModelId=55583A7F02F1
class CADesc : public Descriptor
{
  public:
    //##ModelId=55583A9E026C
    CADesc();

    //##ModelId=55583AA70125
    CADesc(uint8_t* data);

    //##ModelId=55583AC803BC
    virtual ~CADesc();

    //##ModelId=55583AF8023D
    uint16_t CA_system_ID;
    //##ModelId=55583B0F01D5
    uint16_t CA_PID;
    //##ModelId=55583B3103C5
    uint8_t* private_data;
};



#endif /* CADESC_H_HEADER_INCLUDED_AAA79354 */
