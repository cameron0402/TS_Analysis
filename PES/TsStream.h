#ifndef _TS_STREAM_H_
#define _TS_STREAM_H_

#include "../def.h"
#include "PES.h"

class TsStream
{
public:
    TsStream();
    ~TsStream();

    void gatherPES(uint16_t pid, uint8_t* ts_packet);
    void analysisPES(PES* pes);

    uint8_t stream_type;
    uint16_t stream_pid;

    // vedio 
    /*uint8_t vedio_format;
    uint16_t horizontal_pixel;
    uint16_t vertical_pixel;
    uint8_t frame_rate;
    float transport_rate;
    uint16_t width;
    uint16_t height;
    uint8_t color_format;*/

    //audio
    //uint8_t layer;
    /*.....*/

    PES* ref_pes;
    
};

#endif