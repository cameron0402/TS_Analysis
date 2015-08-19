#ifndef SDT_H_HEADER_INCLUDED_AA9C3B80
#define SDT_H_HEADER_INCLUDED_AA9C3B80

#include "../Section.h"

class Descriptor;

//##ModelId=5563CBA7031B
class SDT : public Section
{
  public:
    class ServiceInfo
    {
      public:
        ServiceInfo(uint8_t* data);
        virtual ~ServiceInfo();

        uint16_t service_id;
        bool EIT_schedule_flag;
        bool EIT_present_following_flag;
        uint8_t running_status;
        bool free_CA_mode;
        uint16_t descriptors_loop_length;
        std::list<Descriptor*> desc_list;
    };

    SDT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~SDT();

    virtual bool joinTo(TSFactory* sf);
    bool operator ==(const SDT& st);
    bool operator <(const SDT& st);

    virtual void resolved();
    virtual void getDetail();

    uint16_t transport_stream_id;
    uint8_t version_number;
    bool current_next_indicator;
    uint8_t section_number;
    uint8_t last_section_number;
    uint16_t original_network_id;
    std::list<ServiceInfo*> service_list;
    uint32_t crc32;
};

#endif /* SDT_H_HEADER_INCLUDED_AA9C3B80 */
