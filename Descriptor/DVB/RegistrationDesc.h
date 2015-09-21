#ifndef REGISTRATIONDESC_H_HEADER_INCLUDED_AAA7BBEE
#define REGISTRATIONDESC_H_HEADER_INCLUDED_AAA7BBEE
#include "../Descriptor.h"

//descriptor_tag = 0x05

//##ModelId=555830DA0266
class RegistrationDesc : public Descriptor
{
  public:

    RegistrationDesc(uint8_t* data);
    virtual ~RegistrationDesc();

    uint32_t format_identifier;
    uint8_t* additional_identification_info;
};



#endif /* REGISTRATIONDESC_H_HEADER_INCLUDED_AAA7BBEE */
