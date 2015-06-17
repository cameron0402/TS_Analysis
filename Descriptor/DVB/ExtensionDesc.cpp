#include "ExtensionDesc.h"

//##ModelId=555D4AE901DF
ExtensionDesc::ExtensionDesc()
{
}

//##ModelId=555D4AEB015F
ExtensionDesc::ExtensionDesc(uint8_t* data)
    : Descriptor(data),
      descriptor_tag_extension(data[2])
{
    selector = new uint8_t[length - 1];
    memcpy(selector, data + 3, length - 1);
}

//##ModelId=555D4AED0017
ExtensionDesc::~ExtensionDesc()
{
    delete []selector;
}

