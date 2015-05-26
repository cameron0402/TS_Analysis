#include "TDT.h"
#include "SectionFactory.h"

//##ModelId=556406A303DC
TDT::TDT()
{
}

//##ModelId=556406A801F1
TDT::TDT(uint8_t* data, uint16_t len)
    : Section(data, len),
      UTC_time((data[3] << 32) | (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7])
{
}

//##ModelId=556406AC01FA
TDT::~TDT()
{
}

bool TDT::joinTo(SectionFactory* sf)
{
    if(sf->tdt != NULL)
        return false;
    
    sf->tdt = this;
    return true;
}

