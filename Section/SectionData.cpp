#include "SectionData.h"

//##ModelId=555EC4060105
SectionData::SectionData()
    : PID(-1),
      section_data_length(0),
      section_data(new uint8_t[MAX_SECTION_LENGTH]),
      continuity_counter(INVALID_CC),
      discontinuity_flag(false),
      recv_length(0)
{    
}

//##ModelId=555EC41A0158
SectionData::~SectionData()
{
    delete []section_data;
}

//##ModelId=555EC45001F6
void SectionData::Reset()
{
    PID = -1;
    section_data_length = 0;
    continuity_counter = INVALID_CC;
    discontinuity_flag = false;
    recv_length = 0;
}

