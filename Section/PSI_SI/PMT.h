#ifndef PMT_H_HEADER_INCLUDED_AAAA7F38
#define PMT_H_HEADER_INCLUDED_AAAA7F38
#include "../Section.h"
class Descriptor;

//##ModelId=555569F70169
class PMT : public Section
{
  public:
    //##ModelId=55558221017D
    class StreamInfo
    {
      public:
        //##ModelId=555D7D58002F
        StreamInfo();

        //##ModelId=555D7D6A03E1
        StreamInfo(uint8_t* data);

        //##ModelId=555D7D6D016C
        //##ModelId=555D7D6D016C
        virtual ~StreamInfo();

        // stream_type
        //##ModelId=55558250017E
        uint8_t type;
        // elementary_PID
        //##ModelId=5555826F0328
        uint16_t elem_PID;
        // ES_info_length
        //##ModelId=5555829203E6
        uint16_t info_length;
        //##ModelId=555582AE03CD
        std::list<Descriptor*> desc_list;
    };

    //##ModelId=55556B720001
    PMT();

    //##ModelId=55556B820369
    PMT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    //##ModelId=5558288B00A9
    virtual ~PMT();

    virtual bool joinTo(SectionFactory* sf);
    virtual void resolved();
    virtual void getDetail(uint8_t* data, uint16_t len);
    bool operator ==(const PMT& pt);
    bool operator <(const PMT& pt);

    //##ModelId=5562969D029A
    uint16_t program_number;
    //##ModelId=5562989F030C
    bool current_next_indicator;
    //##ModelId=556296B303D2
    uint8_t version_number;
    //##ModelId=556296DA0299
    uint8_t section_number;
    //##ModelId=5562971A00DC
    uint8_t last_section_number;

    //##ModelId=55556A4E0217
    uint16_t PCR_PID;
    //##ModelId=55556A820381
    uint16_t program_info_length;
    //##ModelId=55556ACF0381
    std::list<StreamInfo*> stream_list;
    //##ModelId=555D747E003D
    std::list<Descriptor*> desc_list;
    
    //##ModelId=5562973302FB
    uint32_t crc32;
};

#endif /* PMT_H_HEADER_INCLUDED_AAAA7F38 */
