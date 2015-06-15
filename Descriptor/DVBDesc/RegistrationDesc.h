#ifndef REGISTRATIONDESC_H_HEADER_INCLUDED_AAA7BBEE
#define REGISTRATIONDESC_H_HEADER_INCLUDED_AAA7BBEE
#include "../Descriptor.h"

//descriptor_tag = 0x05

//##ModelId=555830DA0266
class RegistrationDesc : public Descriptor
{
  public:
    //##ModelId=555831B202CA
    RegistrationDesc();

    //##ModelId=555831BF009B
    RegistrationDesc(uint8_t* data);

    //##ModelId=555831EC01D2
    virtual ~RegistrationDesc();

    //##ModelId=5558316B00CA
    uint32_t format_identifier;
    //##ModelId=555831950172
    uint8_t* additional_identification_info;
};



#endif /* REGISTRATIONDESC_H_HEADER_INCLUDED_AAA7BBEE */
