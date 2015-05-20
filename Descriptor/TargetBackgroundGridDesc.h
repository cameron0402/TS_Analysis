#ifndef TARGETBACKGROUNDGRIDDESC_H_HEADER_INCLUDED_AAA7FBD4
#define TARGETBACKGROUNDGRIDDESC_H_HEADER_INCLUDED_AAA7FBD4
#include "Descriptor.h"

//descriptor_tag = 0x07

//##ModelId=555834C401F6
class TargetBackgroundGridDesc : public Descriptor
{
  public:
    //##ModelId=555834FD016C
    TargetBackgroundGridDesc();

    //##ModelId=5558350D030C
    TargetBackgroundGridDesc(uint8_t* data);

    //##ModelId=5558353E0313
    virtual ~TargetBackgroundGridDesc();

    //##ModelId=55583556031B
    uint16_t horizontal_size;
    //##ModelId=5558356B006B
    uint16_t vertical_size;
    //##ModelId=5558357C02F2
    uint8_t pel_aspect_ratio;
};



#endif /* TARGETBACKGROUNDGRIDDESC_H_HEADER_INCLUDED_AAA7FBD4 */
