#include "Section.h"

Section::Section()
{

}

Section::Section(uint8_t* data, uint16_t len)
    : table_id(data[0]),
      syntax_indicator(data[1] >> 7),
      private_indicator((data[1] >> 6) & 0x01),
      length((data[1] & 0x0F) << 8 | data[2]),
      extension((data[3] << 8) | data[4]), 
      version((data[5] >> 1) & 0x1F),
      current_next(data[5] >> 7),
      number(data[6]),
      last_number(data[7]),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
}

Section::~Section()
{

}

//##ModelId=5555540B00A0
void Section::joinTo(SectionFactory& sf)
{
}

//##ModelId=555561E1025F
void Section::resolved()
{
}

