#ifndef PRIVATEDATASPECIFIERDESC_H_HEADER_INCLUDED_AAA3CEB4
#define PRIVATEDATASPECIFIERDESC_H_HEADER_INCLUDED_AAA3CEB4
#include "../Descriptor.h"

//descriptor_tag = 0x5F
class PrivateDataSpecifierDesc : public Descriptor
{
  public:
    PrivateDataSpecifierDesc(uint8_t* data);
    virtual ~PrivateDataSpecifierDesc();
    uint32_t private_data_specifier;
};



#endif /* PRIVATEDATASPECIFIERDESC_H_HEADER_INCLUDED_AAA3CEB4 */
