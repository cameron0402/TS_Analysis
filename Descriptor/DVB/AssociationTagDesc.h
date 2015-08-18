#ifndef _ASSOCIATION_TAG_DESC_
#define _ASSOCIATION_TAG_DESC_

#include "../Descriptor.h"

//descriptor_tag = 0x14
class AssociationTagDesc : public Descriptor
{
public:
    AssociationTagDesc(uint8_t* data);
    virtual ~AssociationTagDesc();
    uint16_t association_tag;
    uint16_t use;
    uint8_t selector_length;
    uint32_t transaction_id;
    uint32_t time_out;
    //uint8_t* selector;
};

#endif