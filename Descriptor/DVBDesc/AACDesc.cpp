#include "AACDesc.h"

//##ModelId=555D487E0062
AACDesc::AACDesc()
{
}

//##ModelId=555D48800042
AACDesc::AACDesc(uint8_t* data)
    : Descriptor(data),
      profile_and_level(data[2]),
      AAC_type_flag(data[3] >> 7)
{
    int index = 4;
    if(AAC_type_flag)
    {
        AAC_type = data[index++];
    }

    add_info = new uint8_t[length + 2 - index];
    memcpy(add_info, data + index, length + 2 - index);
}

//##ModelId=555D4881039A
AACDesc::~AACDesc()
{
    delete []add_info;
}

