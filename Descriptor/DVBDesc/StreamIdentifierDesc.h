#ifndef STREAMIDENTIFIERDESC_H_HEADER_INCLUDED_AAA50A22
#define STREAMIDENTIFIERDESC_H_HEADER_INCLUDED_AAA50A22
#include "../Descriptor.h"

//descriptor_tag = 0x52
//##ModelId=555AF0210232
class StreamIdentifierDesc : public Descriptor
{
  public:
    //##ModelId=555AF0580055
    StreamIdentifierDesc();

    //##ModelId=555AF06F0115
    StreamIdentifierDesc(uint8_t* data);

    //##ModelId=555AF0800135
    virtual ~StreamIdentifierDesc();

    virtual void resolved();

    //##ModelId=555AF03800A5
    uint8_t component_tag;
};



#endif /* STREAMIDENTIFIERDESC_H_HEADER_INCLUDED_AAA50A22 */
