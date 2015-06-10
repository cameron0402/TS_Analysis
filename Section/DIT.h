#ifndef DIT_H_HEADER_INCLUDED_AA9A9390
#define DIT_H_HEADER_INCLUDED_AA9A9390

#include "Section.h"

//##ModelId=556428200350
class DIT : public Section
{
  public:
    //##ModelId=556428610360
    DIT();

    //##ModelId=556428670050
    DIT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);

    //##ModelId=5564286A0230
    virtual ~DIT();

    //##ModelId=5564283E0177
    bool transition_flag;
};



#endif /* DIT_H_HEADER_INCLUDED_AA9A9390 */
