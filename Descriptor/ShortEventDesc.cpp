#include "ShortEventDesc.h"

//##ModelId=555AABE400CA
ShortEventDesc::ShortEventDesc()
{
}

//##ModelId=555AABF40041
ShortEventDesc::ShortEventDesc(uint8_t* data)
    : Descriptor(data),
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

//##ModelId=555AAC0C03A9
ShortEventDesc::~ShortEventDesc()
{
    delete []event_name;
    delete []text;
}

void ShortEventDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

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

    tmp = new TiXmlElement("event_name");
    tmp->LinkEndChild(new TiXmlText((const char*)event_name));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", text_length);
    tmp = new TiXmlElement("text_length");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    tmp = new TiXmlElement("text");
    tmp->LinkEndChild(new TiXmlText((const char*)text));
    xml->LinkEndChild(tmp);
}

