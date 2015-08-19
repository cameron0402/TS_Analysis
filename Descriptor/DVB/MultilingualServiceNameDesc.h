#ifndef MULTILINGUALSERVICENAMEDESC_H_HEADER_INCLUDED_AAA3B2F6
#define MULTILINGUALSERVICENAMEDESC_H_HEADER_INCLUDED_AAA3B2F6
#include "../Descriptor.h"

//descriptor_tag = 0x5D
class MultilingualServiceNameDesc : public Descriptor
{
  public:
    class ServiceInfo
    {
      public:
        ServiceInfo(uint8_t* data);
        ServiceInfo(const ServiceInfo& sif);
        virtual ~ServiceInfo();

        uint8_t ISO6392_language[4];
        uint8_t service_provider_name_length;
        uint8_t* service_provider_name;
        uint8_t service_name_length;
        uint8_t* service_name;
    };

    MultilingualServiceNameDesc(uint8_t* data);
    virtual ~MultilingualServiceNameDesc();

    virtual void resolved();

    std::list<ServiceInfo*> service_list;
};



#endif /* MULTILINGUALSERVICENAMEDESC_H_HEADER_INCLUDED_AAA3B2F6 */
