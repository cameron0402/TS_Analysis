#ifndef _TS_DATA_H_
#define _TS_DATA_H_

#include "../def.h"
#include "../PES/PES.h"

typedef struct _ts_type
{
    int type;
    char sdes[64];
}ts_type;

class TSData
{
  public:
    enum {INVALID_CC = 0x10};
    enum {MAX_TS_LENGTH = 65536};

    TSData(uint16_t pid);
    virtual ~TSData();

    void Reset();
    void getPES();
    uint32_t get_crc();

    uint16_t PID;
    ts_type type;
    uint8_t continuity_counter;
    bool discontinuity_flag;
    bool scrambling_flag;

    uint32_t ts_data_length;
    uint8_t* ts_data;
    uint32_t recv_length;
 
    uint32_t crc;
    uint32_t pkt_num;

    LimitQueue<uint32_t> pcr_pkt_list;
    double max_bit_rate;
    double min_bit_rate;
    double cur_bit_rate;

    PES* pes;
    bool recv_flag;
};

#endif 
