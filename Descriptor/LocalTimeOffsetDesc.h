#ifndef LOCALTIMEOFFSETDESC_H_HEADER_INCLUDED_AAA47F0B
#define LOCALTIMEOFFSETDESC_H_HEADER_INCLUDED_AAA47F0B
#include "Descriptor.h"

// descriptor_tag = 0x58
//##ModelId=555BEA1300ED
class LocalTimeOffsetDesc : public Descriptor
{
  public:
    //##ModelId=555BEA340233
    class TimeOffsetInfo
    {
      public:
        //##ModelId=555BEA6C02CE
        uint8_t country_code[3];
        //##ModelId=555BEA83026E
        uint8_t country_region_id;
        //##ModelId=555BEA9C016A
        uint8_t local_time_offset_polarity;
        //##ModelId=555BEABA0293
        uint16_t local_time_offset;
        //##ModelId=555BEB9F00AF
        uint64_t time_of_change;
        //##ModelId=555BEBBB0327
        uint16_t next_time_offset;
    };

    //##ModelId=555BEC1F03B6
    LocalTimeOffsetDesc();

    //##ModelId=555BEC2A0276
    LocalTimeOffsetDesc(uint8_t* data);

    //##ModelId=555BEC43035D
    virtual ~LocalTimeOffsetDesc();

    //##ModelId=555BEBDF0220
    std::list<TimeOffsetInfo> timeoff_list;
};



#endif /* LOCALTIMEOFFSETDESC_H_HEADER_INCLUDED_AAA47F0B */
