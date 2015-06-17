#ifndef _NAME_DESC_H_
#define _NAME_DESC_H_

#include "../Descriptor.h"

//descriptor_tag = 0x02
class NameDesc : public Descriptor
{
public:
    NameDesc();
    NameDesc(uint8_t* data);
    virtual ~NameDesc();

    uint8_t* name;
};

#endif