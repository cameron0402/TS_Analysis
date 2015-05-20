#ifndef DESCRIPTOR_H_HEADER_INCLUDED_AAAA1B0A
#define DESCRIPTOR_H_HEADER_INCLUDED_AAAA1B0A

#include "../def.h"

//##ModelId=555568F800DB
class Descriptor
{
  public:
    Descriptor();

    Descriptor(uint8_t* data);

    virtual ~Descriptor();

    //##ModelId=5555699A0028
    virtual void resolved();

    // descriptor_tag
    //##ModelId=5555690800F1
    uint8_t tag;
    // descriptor_length
    //##ModelId=555569480198
    uint8_t length;
};



#endif /* DESCRIPTOR_H_HEADER_INCLUDED_AAAA1B0A */
