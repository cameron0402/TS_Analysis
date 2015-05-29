#ifndef SMOOTHINGBUFFERDESC_H_HEADER_INCLUDED_AAA6B616
#define SMOOTHINGBUFFERDESC_H_HEADER_INCLUDED_AAA6B616
#include "Descriptor.h"

//descriptor_tag = 0x10
//##ModelId=5559602F0016
class SmoothingBufferDesc : public Descriptor
{
  public:
    //##ModelId=555960890314
    SmoothingBufferDesc();

    //##ModelId=5559609503B3
    SmoothingBufferDesc(uint8_t* data);

    //##ModelId=555960B8034B
    virtual ~SmoothingBufferDesc();

    virtual void resolved();

    //##ModelId=555960430225
    uint32_t sb_leak_rate;
    //##ModelId=55596065024D
    uint32_t sb_size;
};



#endif /* SMOOTHINGBUFFERDESC_H_HEADER_INCLUDED_AAA6B616 */
