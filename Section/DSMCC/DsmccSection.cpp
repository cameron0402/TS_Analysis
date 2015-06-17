#include "DsmccSection.h"

DsmccSection::DsmccSection()
{

}

DsmccSection::DsmccSection(uint8_t* data, uint16_t len, uint32_t crc /* = 0xFFFFFFFF */)
    : Section(data, len, crc),
      table_id_extension((data[3] << 8) | data[4]),
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      crc((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    dsmcc_data = new uint8_t[len - 12];
    memcpy(dsmcc_data, data + 8, len - 12);
}

DsmccSection::~DsmccSection()
{
    if(dsmcc_data)
        delete []dsmcc_data;
}