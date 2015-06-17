#ifndef _MODULE_LINK_DESC_
#define _MODULE_LINK_DESC_

#include "../Descriptor.h"

//descriptor_tag = 0x04
class ModuleLinkDesc : public Descriptor
{
public:
    ModuleLinkDesc();
    ModuleLinkDesc(uint8_t* data);
    virtual ~ModuleLinkDesc();

    uint8_t position;
    uint16_t module_id; 
};

#endif