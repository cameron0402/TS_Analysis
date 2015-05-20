#include "HierarchyDesc.h"

//##ModelId=55582F990002
HierarchyDesc::HierarchyDesc()
{
}

//##ModelId=55582FA4037A
HierarchyDesc::HierarchyDesc(uint8_t* data) 
    : Descriptor(data),
      hierarchy_type(data[2] & 0x0F),
      hierarchy_layer_index(data[3] & 0x3F),
      hierarchy_embedded_layer(data[4] & 0x3F),
      hierarchy_priority(data[5] & 0x3F)
{ 
}

//##ModelId=55582FCE01C3
HierarchyDesc::~HierarchyDesc()
{
}

