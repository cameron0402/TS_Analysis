#ifndef SECTIONDATA_H_HEADER_INCLUDED_AAA10F85
#define SECTIONDATA_H_HEADER_INCLUDED_AAA10F85

#include "../def.h"

//##ModelId=555EBFC0003F
class SectionData
{
  public:
      enum {INVALID_CC = 0x10};
      enum {MAX_SECTION_LENGTH = 4096};
    //##ModelId=555EC4060105
    SectionData();

    //##ModelId=555EC41A0158
    virtual ~SectionData();

    //##ModelId=555EC45001F6
    void Reset();

    //##ModelId=555EBFD90065
    int16_t PID;
    //##ModelId=555EBFEF00CD
    uint16_t section_data_length;
    //##ModelId=555EC008001C
    uint8_t* section_data;
    //##ModelId=555EC2730117
    uint8_t continuity_counter;
    //##ModelId=555EC293030E
    bool discontinuity_flag;
    //##ModelId=555EC32E0065
    uint16_t recv_length;
};



#endif /* SECTIONDATA_H_HEADER_INCLUDED_AAA10F85 */
