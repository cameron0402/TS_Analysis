#ifndef _TS_DATA_H_
#define _TS_DATA_H_

#include "../def.h"
#include "../PES/PES.h"

//##ModelId=555EBFC0003F
class TSData
{
  public:
    enum {INVALID_CC = 0x10};
    enum {MAX_TS_LENGTH = 65536};
    enum ts_type {SECTION, PESDATA};
    TSData(ts_type tp);

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

    PES* pes;
    bool recv_flag;
};

#endif 
