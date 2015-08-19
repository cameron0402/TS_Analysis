#ifndef NIT_H_HEADER_INCLUDED_AAAA2DF4
#define NIT_H_HEADER_INCLUDED_AAAA2DF4
#include "../Section.h"
class Descriptor;

//##ModelId=555584E1029F
class NIT : public Section
{
  public:
    //##ModelId=5555865F036F
    class TransStreamInfo
    {
      public:
        TransStreamInfo(uint8_t* data);
        virtual ~TransStreamInfo();

        uint16_t transport_stream_id;
        uint16_t original_network_id;
        uint16_t transport_descriptors_length;
        std::list<Descriptor*> desc_list;
    };


    NIT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~NIT();
    virtual bool joinTo(TSFactory* sf);
    virtual void resolved();
    virtual void getDetail();
    bool operator ==(const NIT& nt);
    bool operator <(const NIT& nt);

    uint16_t network_id;
    uint8_t version_number;
    bool current_next_indicator;
    uint8_t section_number;
    uint8_t last_section_number;

    uint16_t network_descriptors_length;
    std::list<Descriptor*> desc_list;
    uint16_t transport_stream_loop_length;
    std::list<TransStreamInfo*> streaminfo_list;
    uint32_t crc32; 
};

#endif /* NIT_H_HEADER_INCLUDED_AAAA2DF4 */
