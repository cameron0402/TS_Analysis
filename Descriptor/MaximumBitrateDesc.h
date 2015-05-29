#ifndef MAXIMUMBITRATEDESC_H_HEADER_INCLUDED_AAA69147
#define MAXIMUMBITRATEDESC_H_HEADER_INCLUDED_AAA69147
#include "Descriptor.h"

//descriptor_tag = 0x0E
//##ModelId=55594EB203D2
class MaximumBitrateDesc : public Descriptor
{
  public:
    //##ModelId=55594F0D022F
    MaximumBitrateDesc();

    //##ModelId=55594F16039F
    MaximumBitrateDesc(uint8_t* data);

    //##ModelId=55594F3B0177
    virtual ~MaximumBitrateDesc();

    virtual void resolved();

    //##ModelId=55594EE40070
    uint32_t maximum_bitrate;
};



#endif /* MAXIMUMBITRATEDESC_H_HEADER_INCLUDED_AAA69147 */
