#ifndef _PCR_H_
#define _PCR_H_

#include "../def.h"

class PCR
{
public:
    PCR(uint16_t pd, uint32_t sz);
    ~PCR();

    void push_pcr(uint64_t pcr);
    bool operator==(const PCR& pcr);
  
    uint16_t pid;
    uint32_t size;
    
    uint32_t st_pkt_idx;
    uint32_t ed_pkt_idx;
    int64_t intv;

    std::list<uint64_t> time_list;
};

#endif