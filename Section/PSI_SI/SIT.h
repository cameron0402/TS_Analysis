#ifndef SIT_H_HEADER_INCLUDED_AA9AB17A
#define SIT_H_HEADER_INCLUDED_AA9AB17A

#include "../Section.h"

class Descriptor;

class SIT : public Section
{
  public:

    class ServiceInfo
    {
      public:
        ServiceInfo(uint8_t* data);
        virtual ~ServiceInfo();

        uint16_t service_id;
        uint8_t running_status;
        uint16_t service_loop_length;
        std::list<Descriptor*> desc_list;
    };

    SIT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~SIT();

    uint8_t version_number;
    bool current_next_indicator;
    uint8_t section_number;
    uint8_t last_section_number;
    uint16_t transmission_info_loop_length;
    std::list<Descriptor*> desc_list;
    std::list<ServiceInfo*> service_list;
    uint32_t crc32;
};



#endif /* SIT_H_HEADER_INCLUDED_AA9AB17A */
