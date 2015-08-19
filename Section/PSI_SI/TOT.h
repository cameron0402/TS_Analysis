#ifndef TOT_H_HEADER_INCLUDED_AA9BEC2E
#define TOT_H_HEADER_INCLUDED_AA9BEC2E

#include "../Section.h"

class Descriptor;

class TOT : public Section
{
  public:
    TOT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~TOT();
    virtual bool joinTo(TSFactory* sf);
    virtual void resolved();
    virtual void getDetail();
    uint8_t UTC_time[5];
    uint16_t descriptors_loop_length;
    std::list<Descriptor*> desc_list;
    uint32_t crc32;
};



#endif /* TOT_H_HEADER_INCLUDED_AA9BEC2E */
