#ifndef CAT_H_HEADER_INCLUDED_AAAA6611
#define CAT_H_HEADER_INCLUDED_AAAA6611
#include "../Section.h"
class Descriptor;


class CAT : public Section
{
  public:
    CAT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~CAT();
    virtual bool joinTo(TSFactory* sf);
    virtual void resolved();
    virtual void getDetail();
    bool operator ==(const CAT& ct);
    bool operator <(const CAT& ct);

    uint8_t version_number;
    bool current_next_indicator;
    uint8_t section_number;
    uint8_t last_section_number;
    std::list<Descriptor*> desc_list;
    
    uint32_t crc32;
};

#endif /* CAT_H_HEADER_INCLUDED_AAAA6611 */
