#include "ISO639LanguageDesc.h"

ISO639LanguageDesc::LanguageInfo::LanguageInfo()
{

}

ISO639LanguageDesc::LanguageInfo::LanguageInfo(uint8_t* data) 
    : lang(),
      audio_type(data[3])
{
    memcpy(lang, data, 3);
}

ISO639LanguageDesc::LanguageInfo::~LanguageInfo()
{

}

ISO639LanguageDesc::ISO639LanguageDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    while(index < length + 2)
    {
        LanguageInfo* li = new LanguageInfo(data + index);
        lang_list.push_back(li);
        index += 4;
    }
}

ISO639LanguageDesc::~ISO639LanguageDesc()
{
    std::list<LanguageInfo*>::iterator lit;
    for(lit = lang_list.begin(); lit != lang_list.end(); ++lit)
    {
        delete (*lit);
    }
    lang_list.clear();
}

void ISO639LanguageDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("ISO_639_language_descriptor");

    if(!lang_list.empty())
    {
        tmp = new TiXmlElement("language");
        std::list<LanguageInfo*>::iterator lit;
        for(lit = lang_list.begin(); lit != lang_list.end(); ++lit)
        {
            TiXmlElement* tms = new TiXmlElement("ISO_639_language_code");
            tms->LinkEndChild(new TiXmlText((const char*)(*lit)->lang));
            tmp->LinkEndChild(tms);

            tms = new TiXmlElement("autio_type");
            sprintf(arr, "0x%x", (*lit)->audio_type);
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);
        }
        xml->LinkEndChild(tmp);        
    }
}

