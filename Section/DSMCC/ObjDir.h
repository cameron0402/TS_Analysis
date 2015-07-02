#ifndef _OBJ_DIR_H_
#define _OBJ_DIR_H_

#include "ObjDsmcc.h"
#include "IOP_IOR.h"

class Binding
{
public:
    Binding(uint8_t* data);
    ~Binding();
    //bool operator <(const Binding& bd);
    //bool operator ==(const Binding& bd);

    BIOP_Name* bname;
    uint8_t binding_type;
    IOP_IOR* iop_ior;
    uint16_t object_info_length;
    //uint8_t* object_info;
    uint32_t binding_length;
    uint32_t object_key;
};

class ObjDir : public ObjDsmcc
{
public:
    ObjDir(uint8_t* data);
    virtual ~ObjDir();

    //uint8_t* object_info;
    uint8_t service_context_count;
    //uint8_t* service_context_list;
    uint32_t message_body_length;
    uint16_t binding_count;
    std::list<Binding*> binding_list;
};

#endif