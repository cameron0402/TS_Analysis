#include "StreamIdentifierDesc.h"

//##ModelId=555AF0580055
StreamIdentifierDesc::StreamIdentifierDesc()
{
}

//##ModelId=555AF06F0115
StreamIdentifierDesc::StreamIdentifierDesc(uint8_t* data)
    : Descriptor(data),
      component_tag(data[2])
{
}

//##ModelId=555AF0800135
StreamIdentifierDesc::~StreamIdentifierDesc()
{
}

void StreamIdentifierDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("stream_identifier_descriptor");

    sprintf(arr, "0x%x", component_tag);
    tmp = new TiXmlElement("component_tag");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);
}

