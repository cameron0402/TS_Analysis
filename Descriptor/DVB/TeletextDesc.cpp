#include "TeletextDesc.h"

//##ModelId=555AFD7F01E8
TeletextDesc::TeletextDesc()
{
}

//##ModelId=555AFD880150
TeletextDesc::TeletextDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    TextInfo tmp;
    while(index < length + 2)
    {
        memcpy(tmp.ISO6392_language, data + index, 3);
        tmp.teletext_type = data[index + 3] >> 3;
        tmp.teletext_magazine_number = data[index + 3] & 0x7;
        tmp.teletext_page_number = data[index + 4];
        text_list.push_back(tmp);
        index += 5;
    }
}

//##ModelId=555AFD9B0148
TeletextDesc::~TeletextDesc()
{
}

