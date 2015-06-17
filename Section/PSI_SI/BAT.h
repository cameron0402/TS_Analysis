#ifndef BAT_H_HEADER_INCLUDED_AA9D2706
#define BAT_H_HEADER_INCLUDED_AA9D2706
#include "../Section.h"
class Descriptor;

//##ModelId=55628C830124
class BAT : public Section
{
  public:
    //##ModelId=55628F130139
    class TransStreamInfo
    {
      public:
        //##ModelId=55628F4000F1
        TransStreamInfo();

        //##ModelId=55628F4C0029
        TransStreamInfo(uint8_t* data);

        //##ModelId=55628F5903C0
        virtual ~TransStreamInfo();

        //##ModelId=55628F7D0189
        uint16_t transport_stream_id;
        //##ModelId=55628FB90089
        uint16_t original_network_id;
        //##ModelId=55628FC403A8
        uint16_t transport_descriptors_length;
        //##ModelId=55628FDA0381
        std::list<Descriptor*> desc_list;
    };

    //##ModelId=55628C8D03B6
    BAT();
    //##ModelId=55628C9103A7
    BAT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    //##ModelId=55628C96028F
    virtual ~BAT();
    virtual bool joinTo(SectionFactory* sf);
    virtual void getDetail(uint8_t* data, uint16_t len);
    bool operator ==(const BAT& bt);
    //bool operator <(const BAT& bt);

    //##ModelId=5562AF040157
    uint16_t bouquet_id;
    //##ModelId=5562AF3E0111
    uint8_t version_number;
    //##ModelId=5562AF480087
    bool current_next_indicator;
    //##ModelId=5562AF550188
    uint8_t section_number;
    //##ModelId=5562AF60036F
    uint8_t last_section_number;

    //##ModelId=55628CDA00F9
    uint16_t bouquet_descriptors_length;
    //##ModelId=55628D450329
    std::list<Descriptor*> desc_list;
    //##ModelId=55628DDD0302
    uint16_t transport_stream_loop_length;
    //##ModelId=55628ED10378
    std::list<TransStreamInfo*> streaminfo_list;
    
    //##ModelId=5562AF7000A3
    uint32_t crc32;
};



#endif /* BAT_H_HEADER_INCLUDED_AA9D2706 */
