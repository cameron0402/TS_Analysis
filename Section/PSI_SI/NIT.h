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
        //##ModelId=555D8D48003E
        TransStreamInfo();

        //##ModelId=555D8D580325
        //##ModelId=555D8D580325
        TransStreamInfo(uint8_t* data);

        
        //##ModelId=555D8D5B00B0
        virtual ~TransStreamInfo();

        //##ModelId=55558677030F
        uint16_t transport_stream_id;
        //##ModelId=55558698006F
        uint16_t original_network_id;
        //##ModelId=555586CD00F7
        uint16_t transport_descriptors_length;
        //##ModelId=555587030350
        std::list<Descriptor*> desc_list;
    };

    //##ModelId=5555875B00F0
    NIT();

    //##ModelId=55558761023E
    NIT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    //##ModelId=555828A60271
    virtual ~NIT();
    virtual bool joinTo(SectionFactory* sf);
    virtual void resolved();
    virtual void getDetail(uint8_t* data, uint16_t len);
    bool operator ==(const NIT& nt);
    bool operator <(const NIT& nt);
    //##ModelId=5562978900BC
    uint16_t network_id;
    //##ModelId=5562979C021E
    uint8_t version_number;
    //##ModelId=556298BB011B
    bool current_next_indicator;
    //##ModelId=556297AF0252
    uint8_t section_number;
    //##ModelId=556297C00002
    uint8_t last_section_number;

    //##ModelId=555584FE01EE
    uint16_t network_descriptors_length;
    //##ModelId=5555858902AE
    std::list<Descriptor*> desc_list;
    //##ModelId=555586230017
    uint16_t transport_stream_loop_length;
    //##ModelId=555D8D18028A
    std::list<TransStreamInfo*> streaminfo_list;
    //##ModelId=5562990C0113
    uint32_t crc32;
    
};

#endif /* NIT_H_HEADER_INCLUDED_AAAA2DF4 */
