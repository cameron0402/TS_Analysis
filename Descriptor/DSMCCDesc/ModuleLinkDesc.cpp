#include "ModuleLinkDesc.h"

ModuleLinkDesc::ModuleLinkDesc()
{

}

ModuleLinkDesc::ModuleLinkDesc(uint8_t* data)
    : Descriptor(data),
      position(data[2]),
      module_id((data[3] << 8) | data[4])
{

}

ModuleLinkDesc::~ModuleLinkDesc()
{

}