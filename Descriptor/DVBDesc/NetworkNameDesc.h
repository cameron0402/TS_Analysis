#ifndef NETWORKNAMEDESC_H_HEADER_INCLUDED_AAA67A4F
#define NETWORKNAMEDESC_H_HEADER_INCLUDED_AAA67A4F
#include "../Descriptor.h"

//descriptor_tag = 0x40
//##ModelId=55597E890199
class NetworkNameDesc : public Descriptor
{
  public:
    //##ModelId=55597F480343
    NetworkNameDesc();

    //##ModelId=55597F5400B9
    NetworkNameDesc(uint8_t* data);

    //##ModelId=55597F7A01E2
    virtual ~NetworkNameDesc();

    virtual void resolved();

    //##ModelId=55597F8F035B
    uint8_t* network_name;
};



#endif /* NETWORKNAMEDESC_H_HEADER_INCLUDED_AAA67A4F */
