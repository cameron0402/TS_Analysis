#ifndef DIT_H_HEADER_INCLUDED_AA9A9390
#define DIT_H_HEADER_INCLUDED_AA9A9390

#include "../Section.h"

class DIT : public Section
{
  public:
    DIT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~DIT();

    bool transition_flag;
};



#endif /* DIT_H_HEADER_INCLUDED_AA9A9390 */
