#ifndef PMT_H_HEADER_INCLUDED_AAAA7F38
#define PMT_H_HEADER_INCLUDED_AAAA7F38
#include "../Section.h"
class Descriptor;

const int MAX_PCR_NUM = 1000;
const int MAX_PTS_NUM = MAX_PCR_NUM;
const int MAX_DTS_NUM = MAX_PCR_NUM;

class PMT : public Section
{
  public:
    class StreamInfo
    {
      public:
        StreamInfo();
        StreamInfo(uint8_t* data);
        virtual ~StreamInfo();

        uint8_t type;
        uint16_t elem_PID;
        uint16_t info_length;
        std::list<Descriptor*> desc_list;
    };

    PMT();
    PMT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~PMT();

    virtual bool joinTo(TSFactory* sf);
    virtual void resolved();
    virtual void getDetail();
    bool operator ==(const PMT& pt);
    bool operator <(const PMT& pt);

    uint16_t program_number;
    bool current_next_indicator;
    uint8_t version_number;
    uint8_t section_number;
    uint8_t last_section_number;

    uint16_t PCR_PID;
    uint16_t program_info_length;
    std::list<StreamInfo*> stream_list;
    std::list<Descriptor*> desc_list;
    
    uint32_t crc32;
};

class Stream
{
public:
    Stream(PMT::StreamInfo* si);
    ~Stream();

    uint16_t stream_pid;
    uint8_t stream_type;
    bool scrambling;

    LimitQueue<int64_t> pts_list;
    LimitQueue<int64_t> dts_list;
};

class Program
{
public:
    Program(PMT* pt);
    ~Program();

    uint16_t program_number;
    uint16_t pcr_pid;
    bool scrambling;
 
    LimitQueue<int64_t> pcr_list;
    LimitQueue<uint32_t> pcr_pkt_list; 
    std::list<Stream*> stream_list;
};

#endif /* PMT_H_HEADER_INCLUDED_AAAA7F38 */
