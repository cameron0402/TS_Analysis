#include "DIT.h"

//##ModelId=556428610360
DIT::DIT()
{
}

//##ModelId=556428670050
DIT::DIT(uint8_t* data, uint16_t len, uint32_t crc)
    : Section(data, len),
      transition_flag(data[2] >> 7)
{
}

//##ModelId=5564286A0230
DIT::~DIT()
{
}

