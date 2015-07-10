#include "PCR.h"

PCR::PCR(uint16_t pd, uint32_t sz)
    :pid(pd),
     size(sz),
     st_pkt_idx(0),
     ed_pkt_idx(0),
     intv(0),
     time_list()
{

};

PCR::~PCR()
{

}

void PCR::push_pcr(uint64_t pcr)
{
    if(time_list.size() >= size)
    {
        time_list.pop_front();
    }
    time_list.push_back(pcr);
}


