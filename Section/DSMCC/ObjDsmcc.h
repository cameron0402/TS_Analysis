#ifndef _OBJ_DSMCC_H_
#define _OBJ_DSMCC_H_

#include "../../def.h"

class ObjDsmcc
{
public:
    ObjDsmcc();
    ObjDsmcc(uint8_t* data);
    virtual ~ObjDsmcc();
    virtual int uncompressObj();

    bool operator <(const ObjDsmcc& odc);
    bool operator ==(const ObjDsmcc& odc);

    uint8_t magic[4]; //BIOP
    uint8_t version_major; //0x01
    uint8_t version_minor; //0x00
    uint8_t byte_order; //0x00

    uint8_t message_type; //0x00
    uint32_t message_size; 

    uint8_t object_key_length;
    uint32_t object_key;

    uint32_t object_kind_length;
    uint8_t object_kind[4]; 

    uint16_t object_info_length;
    //uint8_t* object_info;

    uint32_t obj_length;
    ObjDsmcc* parent;
};

class ObjFactory
{
public:
    ObjDsmcc* createObj(uint8_t* data);
};

#endif