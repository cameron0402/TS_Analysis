#ifndef BAT_H_HEADER_INCLUDED_AA9D2706
#define BAT_H_HEADER_INCLUDED_AA9D2706
#include "../Section.h"
class Descriptor;

class BAT : public Section
{
  public:
    class TransStreamInfo
    {
      public:

        TransStreamInfo();
        TransStreamInfo(uint8_t* data);
        virtual ~TransStreamInfo();

        uint16_t transport_stream_id;
        uint16_t original_network_id;
        uint16_t transport_descriptors_length;
        std::list<Descriptor*> desc_list;
    };

    BAT();
    BAT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~BAT();
    virtual bool joinTo(TSFactory* sf);
    virtual void getDetail();
    bool operator ==(const BAT& bt);
    bool operator <(const BAT& bt);

    uint16_t bouquet_id;
    uint8_t version_number;
    bool current_next_indicator;
    uint8_t section_number;
    uint8_t last_section_number;

    uint16_t bouquet_descriptors_length;
    std::list<Descriptor*> desc_list;
    uint16_t transport_stream_loop_length;
    std::list<TransStreamInfo*> streaminfo_list;
   
    uint32_t crc32;
};



#endif /* BAT_H_HEADER_INCLUDED_AA9D2706 */
