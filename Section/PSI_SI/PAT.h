#ifndef PAT_H_HEADER_INCLUDED_AAAA7CE5
#define PAT_H_HEADER_INCLUDED_AAAA7CE5
#include "../Section.h"

class ProgInfo;

class PAT : public Section
{
  public:
    PAT();
    PAT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);

    virtual ~PAT();
    virtual bool joinTo(TSFactory* sf);
    virtual void resolved();
    virtual void getDetail();

    bool operator ==(const PAT& pt);

    uint16_t transport_stream_id;
    uint8_t version_number;
    bool current_next_indicator;
    uint8_t section_number;
    uint8_t last_section_number;
    std::list<ProgInfo*> prog_list;
    uint32_t crc32;
};



#endif /* PAT_H_HEADER_INCLUDED_AAAA7CE5 */
