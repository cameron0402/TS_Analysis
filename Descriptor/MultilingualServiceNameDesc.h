#ifndef MULTILINGUALSERVICENAMEDESC_H_HEADER_INCLUDED_AAA3B2F6
#define MULTILINGUALSERVICENAMEDESC_H_HEADER_INCLUDED_AAA3B2F6
#include "Descriptor.h"

//descriptor_tag = 0x5D
//##ModelId=555C21BB03CF
class MultilingualServiceNameDesc : public Descriptor
{
  public:
    //##ModelId=555C21FC018B
    class ServiceInfo
    {
      public:
        //##ModelId=555C229901ED
        ServiceInfo();

        //##ModelId=555C22A00165
        ServiceInfo(const ServiceInfo& sif);

        //##ModelId=555C22A5032C
        virtual ~ServiceInfo();

        //##ModelId=555C22200153
        uint8_t ISO6392_language[3];
        //##ModelId=555C223B001C
        uint8_t service_provider_name_length;
        //##ModelId=555C225200DE
        uint8_t* service_provider_name;
        //##ModelId=555C227501F3
        uint8_t service_name_length;
        //##ModelId=555C228701B3
        uint8_t* service_name;
    };

    //##ModelId=555C22F0024C
    MultilingualServiceNameDesc();

    //##ModelId=555C22FC0065
    MultilingualServiceNameDesc(uint8_t* data);

    //##ModelId=555C230C0313
    virtual ~MultilingualServiceNameDesc();

    //##ModelId=555C22CB0383
    std::list<ServiceInfo> service_list;
};



#endif /* MULTILINGUALSERVICENAMEDESC_H_HEADER_INCLUDED_AAA3B2F6 */
