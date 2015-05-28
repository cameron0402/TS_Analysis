#include "Section.h"
#include "SectionFactory.h"

Section::Section() : xml(NULL)
{

}

Section::Section(uint8_t* data, uint16_t len)
    : table_id(data[0]),
      syntax_indicator(data[1] >> 7),
      private_indicator((data[1] >> 6) & 0x01),
      length((data[1] & 0x0F) << 8 | data[2]),
      xml(NULL)
{
}

Section::~Section()
{

}

//##ModelId=5555540B00A0
bool Section::joinTo(SectionFactory* sf)
{
    return false;
}

//##ModelId=555561E1025F
void Section::resolved()
{
}

