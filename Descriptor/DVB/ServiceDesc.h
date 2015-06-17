#ifndef SERVICEDESC_H_HEADER_INCLUDED_AAA531FF
#define SERVICEDESC_H_HEADER_INCLUDED_AAA531FF
#include "../Descriptor.h"

//descriptor_tag = 0x48
//##ModelId=555A8EB30272
class ServiceDesc : public Descriptor
{
  public:
    //##ModelId=555A8EC10111
    ServiceDesc();

    //##ModelId=555A8EC70294
    ServiceDesc(uint8_t* data);

    //##ModelId=555A8EE702F1
    virtual ~ServiceDesc();

    virtual void resolved();

    //##ModelId=555A8EFC0363
    uint8_t service_type;
    //##ModelId=555A8F190231
    uint8_t service_provider_length;
    //##ModelId=555A8F360020
    uint8_t* service_provider;
    //##ModelId=555A8F4802CA
    uint8_t service_name_length;
    //##ModelId=555A8F4E0048
    uint8_t* service_name;
};



#endif /* SERVICEDESC_H_HEADER_INCLUDED_AAA531FF */
