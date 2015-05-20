#include "VBITeletextDesc.h"

//##ModelId=555A8A53013F
VBITeletextDesc::VBITeletextDesc()
{
}

//##ModelId=555A8A6501CF
VBITeletextDesc::VBITeletextDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    TeletextInfo tmp;
    while(index < length + 1)
    {
        memcpy(tmp.ISO639_language, data + index, 3);
        tmp.teletext_type = data[index + 3] >> 3;
        tmp.teletext_magazine_number = data[index + 3] & 0x7;
        tmp.teletext_page_number = data[index + 4];
        teletext_list.push_back(tmp);
        index += 5;
    }
}

//##ModelId=555A8A7F0146
VBITeletextDesc::~VBITeletextDesc()
{
}

