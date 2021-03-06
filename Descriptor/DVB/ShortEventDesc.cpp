#include "ShortEventDesc.h"

ShortEventDesc::ShortEventDesc(uint8_t* data)
    : Descriptor(data),
      ISO6392_language(),
      event_name_length(data[5]),
      text_length(data[6 + event_name_length])
{
    memcpy(ISO6392_language, data + 2, 3);
    event_name = new uint8_t[event_name_length + 1];
    event_name[event_name_length] = 0;
    memcpy(event_name, data + 6, event_name_length);

    text = new uint8_t[text_length + 1];
    text[text_length] = 0;
    memcpy(text, data + 7 + event_name_length, text_length);
}

ShortEventDesc::~ShortEventDesc()
{
    delete []event_name;
    delete []text;
}

void ShortEventDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[256] = {0};

    Descriptor::resolved();
    xml->SetValue("short_event_descriptor");

    memcpy(arr, ISO6392_language, 3);
    arr[3] = 0;
    tmp = new TiXmlElement("ISO_639_2_language_code");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", event_name_length);
    tmp = new TiXmlElement("event_name_length");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    if(event_name_length > 0)
    {
        coding_string_to_gb(event_name, (uint8_t*)arr, event_name_length);
        tmp = new TiXmlElement("event_name");
        tmp->LinkEndChild(new TiXmlText(arr));
        xml->LinkEndChild(tmp);
    }
    
    sprintf(arr, "0x%x", text_length);
    tmp = new TiXmlElement("text_length");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    if(text_length > 0)
    {
        coding_string_to_gb(text, (uint8_t*)arr, text_length);
        tmp = new TiXmlElement("text");
        tmp->LinkEndChild(new TiXmlText(arr));
        xml->LinkEndChild(tmp);
    }  
}

