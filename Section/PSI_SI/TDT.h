#ifndef TDT_H_HEADER_INCLUDED_AA9BB1E6
#define TDT_H_HEADER_INCLUDED_AA9BB1E6

#include "../Section.h"
class TDT : public Section
{
  public:
    TDT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~TDT();

    virtual bool joinTo(TSFactory* sf);
    virtual void resolved();

    uint8_t UTC_time[5];
};



#endif /* TDT_H_HEADER_INCLUDED_AA9BB1E6 */
