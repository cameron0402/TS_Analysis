#include "DIT.h"

DIT::DIT(uint8_t* data, uint16_t len, uint32_t crc)
    : Section(data, len),
      transition_flag(data[2] >> 7)
{
}

//##ModelId=5564286A0230
DIT::~DIT()
{
}

