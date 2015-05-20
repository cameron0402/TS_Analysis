#include "ISO639LanguageDesc.h"

//##ModelId=555938E30314
ISO639LanguageDesc::ISO639LanguageDesc()
{
}

//##ModelId=555938F30225
ISO639LanguageDesc::ISO639LanguageDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    std::vector<char> lang;
    while(index < length + 2)
    {
        lang.push_back(data[index]);
        lang.push_back(data[index + 1]);
        lang.push_back(data[index + 2]);
        lang_list.push_back(lang);
        index += 3;
    }
    audio_type = data[index];
}

//##ModelId=555939280014
ISO639LanguageDesc::~ISO639LanguageDesc()
{
}

