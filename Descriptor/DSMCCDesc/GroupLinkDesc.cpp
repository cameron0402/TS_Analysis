#include "GroupLinkDesc.h"

GroupLinkDesc::GroupLinkDesc()
{

}

GroupLinkDesc::GroupLinkDesc(uint8_t* data)
    : Descriptor(data), 
      position(data[2]),
      group_id((data[3] << 24) | (data[4] << 16) | (data[5] << 8) | data[6])
{

}

GroupLinkDesc::~GroupLinkDesc()
{

}