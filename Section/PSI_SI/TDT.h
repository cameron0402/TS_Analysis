#ifndef TDT_H_HEADER_INCLUDED_AA9BB1E6
#define TDT_H_HEADER_INCLUDED_AA9BB1E6

#include "../Section.h"
//##ModelId=5564068F015D
class TDT : public Section
{
  public:
    //##ModelId=556406A303DC
    TDT();

    //##ModelId=556406A801F1
    TDT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);

    //##ModelId=556406AC01FA
    virtual ~TDT();

    virtual bool joinTo(TSFactory* sf);

    virtual void resolved();

    //##ModelId=556406DE0301
    uint8_t UTC_time[5];
};



#endif /* TDT_H_HEADER_INCLUDED_AA9BB1E6 */
