#ifndef NETWORKNAMEDESC_H_HEADER_INCLUDED_AAA67A4F
#define NETWORKNAMEDESC_H_HEADER_INCLUDED_AAA67A4F
#include "../Descriptor.h"

//descriptor_tag = 0x40
class NetworkNameDesc : public Descriptor
{
  public:
    NetworkNameDesc(uint8_t* data);
    virtual ~NetworkNameDesc();
    virtual void resolved();
    uint8_t* network_name;
};



#endif /* NETWORKNAMEDESC_H_HEADER_INCLUDED_AAA67A4F */
