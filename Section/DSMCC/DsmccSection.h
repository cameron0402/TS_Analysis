#ifndef _DSMCC_SECTION_H_
#define _DSMCC_SECTION_H_

#include "../Section.h"
#include "DII.h"
#include "DSI.h"

class DsmccSection;

class ESGInfo
{
public:
    ESGInfo(uint16_t ser_id = 0);
    ~ESGInfo();

    void saveDsmccData(DsmccSection* dss);
    void saveDIIInfo(DsmccSection* dss);
    void saveDSIInfo(DsmccSection* dss);
    void saveDDBData(DsmccSection* dss);
    void reset();
    void resolved();
    uint32_t getCheckSum();
    void saveFile(char* save_path);
    void saveFile(char* save_path, ObjDsmcc* od);

    bool recvCompleted();
    bool operator ==(const ESGInfo& ei);

    uint16_t service_id;
    std::list<uint16_t> pid_list;
    DSI* dsi;
    std::set<DII*, cmp_secp<DII>> dii_list;
    std::set<ObjDsmcc*, cmp_secp<ObjDsmcc>> obj_list;

    DII::Module sh_md; //just for search used
    uint32_t check_sum;
};

class DsmccSection : public Section
{
public:
    DsmccSection(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~DsmccSection();

    virtual bool joinTo(TSFactory* sf);
    virtual void resolved();
    void setBelong(ESGInfo* bl);

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