#ifndef EIT_H_HEADER_INCLUDED_AA9C5834
#define EIT_H_HEADER_INCLUDED_AA9C5834

#include "Section.h"

class Descriptor;

//##ModelId=5563DAF801FE
class EIT : public Section
{
  public:
    //##ModelId=5563DC3302C6
    class EventInfo
    {
      public:
        //##ModelId=5563DC4003BF
        EventInfo();

        //##ModelId=5563DC47027B
        EventInfo(uint8_t* data);

        //##ModelId=5563DC4D02E1
        virtual ~EventInfo();

        //##ModelId=5563DC7C023A
        uint16_t event_id;
        //##ModelId=5563DC8F00F6
        uint64_t start_time;
        //##ModelId=5563DCA0010D
        uint32_t duration;
        //##ModelId=5563DCAF03C8
        uint8_t running_status;
        //##ModelId=5563DCC503D7
        bool free_CA_mode;
        //##ModelId=5563DCD703C0
        uint16_t descriptors_loop_length;
        //##ModelId=5563DCEE0387
        std::list<Descriptor*> desc_list;
    };

    //##ModelId=5563DB220128
    EIT();

    //##ModelId=5563DB260334
    EIT(uint8_t* data, uint16_t len);

    //##ModelId=5563DB2B0060
    virtual ~EIT();

    virtual bool joinTo(SectionFactory* sf);
    bool operator ==(const EIT& et);


    //##ModelId=5563DB5E002F
    uint16_t service_id;
    //##ModelId=5563DB6F02C5
    uint8_t version_number;
    //##ModelId=5563DB7F0263
    bool current_next_indicator;
    //##ModelId=5563DB98008B
    uint8_t section_number;
    //##ModelId=5563DBA80144
    uint8_t last_section_number;
    //##ModelId=5563DBBC027D
    uint16_t transport_stream_id;
    //##ModelId=5563DBE80262
    uint16_t original_network_id;
    //##ModelId=5563DBFF0127
    uint8_t segment_last_section_number;
    //##ModelId=5563DC1C016C
    uint8_t last_table_id;
    //##ModelId=5563DD1100A9
    std::list<EventInfo*> event_list;
    //##ModelId=5563E3B0004B
    uint32_t crc32;
};



#endif /* EIT_H_HEADER_INCLUDED_AA9C5834 */
