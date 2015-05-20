#ifndef SHORTSMOOTHINGBUFFERDESC_H_HEADER_INCLUDED_AAA3E6E2
#define SHORTSMOOTHINGBUFFERDESC_H_HEADER_INCLUDED_AAA3E6E2
#include "Descriptor.h"

//descriptor_tag = 0x61
//##ModelId=555C363300E8
class ShortSmoothingBufferDesc : public Descriptor
{
  public:
    //##ModelId=555C364D01D9
    ShortSmoothingBufferDesc();

    //##ModelId=555C365001B6
    ShortSmoothingBufferDesc(uint8_t* data);

    //##ModelId=555C36530040
    virtual ~ShortSmoothingBufferDesc();

    //##ModelId=555C366701E7
    uint8_t sb_size;
    //##ModelId=555C367B03C7
    uint8_t sb_lead_rate;
};



#endif /* SHORTSMOOTHINGBUFFERDESC_H_HEADER_INCLUDED_AAA3E6E2 */
