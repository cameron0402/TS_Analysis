#ifndef _DSMCC_SECTION_H_
#define _DSMCC_SECTION_H_

#include "../Section.h"

class DsmccSection : public Section
{
public:
    DsmccSection();
    DsmccSection(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~DsmccSection();

    uint16_t table_id_extension;
    uint8_t version_number;
    bool current_next_indicator;
    uint8_t section_number;
    uint8_t last_section_number;

    uint8_t* dsmcc_data;

    uint32_t crc;
};

#endif