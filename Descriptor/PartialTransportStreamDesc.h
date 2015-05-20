#ifndef PARTIALTRANSPORTSTREAMDESC_H_HEADER_INCLUDED_AAA3D423
#define PARTIALTRANSPORTSTREAMDESC_H_HEADER_INCLUDED_AAA3D423
#include "Descriptor.h"

//descriptor_tag = 0x63
//##ModelId=555C3A320376
class PartialTransportStreamDesc : public Descriptor
{
  public:
    //##ModelId=555C3A740160
    PartialTransportStreamDesc();

    //##ModelId=555C3A7602E9
    PartialTransportStreamDesc(uint8_t* data);

    //##ModelId=555C3A780302
    virtual ~PartialTransportStreamDesc();

    //##ModelId=555C3A9601C9
    uint32_t peak_rate;
    //##ModelId=555C3AAF02E2
    uint32_t minimum_overall_smoothing_rate;
    //##ModelId=555C3AC402E7
    uint16_t maximum_overall_smoothing_butter;
};



#endif /* PARTIALTRANSPORTSTREAMDESC_H_HEADER_INCLUDED_AAA3D423 */
