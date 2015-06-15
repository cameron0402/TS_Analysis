#ifndef _TYPE_DESC_H_
#define _TYPE_DESC_H_

#include "../Descriptor.h"

//descriptor_tag = 0x01
class TypeDesc : public Descriptor
{
public:
    TypeDesc();
    TypeDesc(uint8_t* data);
    virtual ~TypeDesc();
    uint8_t* type;
};

#endif