#include "ContentDesc.h"

//##ModelId=555AF3270376
ContentDesc::ContentDesc()
{
}

//##ModelId=555AF32E0325
ContentDesc::ContentDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    ContentInfo tmp;
    while(index < length + 2)
    {
        tmp.content_nibble_level_1 = data[index] >> 4;
        tmp.content_nibble_level_2 = data[index] & 0x0F;
        tmp.user_nibble_1 = data[index + 1] >> 4;
        tmp.user_nibble_2 = data[index + 1] & 0x0F;
        content_list.push_back(tmp);
        index += 2;
    }
}

//##ModelId=555AF34201EF
ContentDesc::~ContentDesc()
{
}

