#include "TeletextDesc.h"

TeletextDesc::TextInfo::TextInfo(uint8_t* data)
    : ISO6392_language(),
      teletext_type(data[3] >> 3),
      teletext_magazine_number(data[3] & 0x7),
      teletext_page_number(data[4])
{
    memcpy(ISO6392_language, data, 3);
}

TeletextDesc::TextInfo::~TextInfo()
{

}

TeletextDesc::TeletextDesc(uint8_t* data) 
    : Descriptor(data)
{
    int index = 2;
    TextInfo* tmp;
    while(index < length + 2)
    {
        tmp = new TextInfo(data + index);
        text_list.push_back(tmp);
        index += 5;
    }
}

TeletextDesc::~TeletextDesc()
{
    std::list<TextInfo*>::iterator tit = text_list.begin();
    for(; tit != text_list.end(); ++tit)
        delete (*tit);
}

