#ifndef _DSMCC_SECTION_H_
#define _DSMCC_SECTION_H_

#include "../Section.h"
#include "DII.h"
#include "DSI.h"

class ESGInfo
{
public:
    ESGInfo(uint16_t ser_id = 0);
    ~ESGInfo();

    uint16_t service_id;
    std::list<uint16_t> pid_list;
    DSI* dsi;
    std::list<DII*> dii_list;
};

class DsmccSection : public Section
{
public:
    DsmccSection();
    DsmccSection(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~DsmccSection();

    virtual bool joinTo(SectionFactory* sf);
    virtual void getDetail();
    virtual void resolved();
    void saveDDBData();

    uint16_t table_id_extension;
    uint8_t version_number;
    bool current_next_indicator;
    uint8_t section_number;
    uint8_t last_section_number;
    uint8_t* dsmcc_data;
    uint32_t crc;

    ESGInfo* belong;
};

#endif