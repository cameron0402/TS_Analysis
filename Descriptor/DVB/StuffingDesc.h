#ifndef STUFFINGDESC_H_HEADER_INCLUDED_AAA61E80
#define STUFFINGDESC_H_HEADER_INCLUDED_AAA61E80
#include "../Descriptor.h"

//descriptor_tag = 0x42
//##ModelId=555984E200E3
class StuffingDesc : public Descriptor
{
  public:
    //##ModelId=555985150174
    StuffingDesc();

    //##ModelId=5559851F02A5
    StuffingDesc(uint8_t* data);

    //##ModelId=555985410205
    virtual ~StuffingDesc();

    //##ModelId=55598554034D
    uint8_t* stuffings;
};



#endif /* STUFFINGDESC_H_HEADER_INCLUDED_AAA61E80 */
