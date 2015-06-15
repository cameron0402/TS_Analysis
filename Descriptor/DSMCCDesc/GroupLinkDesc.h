#ifndef _GROUP_LINK_DESC_H_
#define _GROUP_LINK_DESC_H_

#include "../Descriptor.h"
//descriptor_tag = 0x8

class GroupLinkDesc : public Descriptor
{
public:
    GroupLinkDesc();
    GroupLinkDesc(uint8_t* data);
    virtual ~GroupLinkDesc();

    uint8_t position;
    uint32_t group_id;
};

#endif