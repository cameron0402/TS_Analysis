#ifndef PRIVATEDATASPECIFIERDESC_H_HEADER_INCLUDED_AAA3CEB4
#define PRIVATEDATASPECIFIERDESC_H_HEADER_INCLUDED_AAA3CEB4
#include "Descriptor.h"

//descriptor_tag = 0x5F
//##ModelId=555C2AA60166
class PrivateDataSpecifierDesc : public Descriptor
{
  public:
    //##ModelId=555C2AC1014E
    PrivateDataSpecifierDesc();

    //##ModelId=555C2AC303E1
    PrivateDataSpecifierDesc(uint8_t* data);

    //##ModelId=555C2AC601F5
    virtual ~PrivateDataSpecifierDesc();

    //##ModelId=555C2AE30136
    uint32_t private_data_specifier;
};



#endif /* PRIVATEDATASPECIFIERDESC_H_HEADER_INCLUDED_AAA3CEB4 */
