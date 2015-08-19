#ifndef EIT_H_HEADER_INCLUDED_AA9C5834
#define EIT_H_HEADER_INCLUDED_AA9C5834

#include "../Section.h"

class Descriptor;

class EIT : public Section
{
  public:
    class EventInfo
    {
      public:
        EventInfo(uint8_t* data);
        virtual ~EventInfo();

        uint16_t event_id;
        uint8_t start_time[5];
        uint8_t duration[3];
        uint8_t running_status;
        bool free_CA_mode;
        uint16_t descriptors_loop_length;

        std::list<Descriptor*> desc_list;
    };

    EIT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~EIT();

    virtual bool joinTo(TSFactory* sf);
    bool operator ==(const EIT& et);
    bool operator <(const EIT& et);

    virtual void resolved();
    virtual void getDetail();

    uint16_t service_id;
    uint8_t version_number;
    bool current_next_indicator;
    uint8_t section_number;
    uint8_t last_section_number;
    uint16_t transport_stream_id;
    uint16_t original_network_id;
    uint8_t segment_last_section_number;
    uint8_t last_table_id;
    std::list<EventInfo*> event_list;
    uint32_t crc32;
};

#endif /* EIT_H_HEADER_INCLUDED_AA9C5834 */
