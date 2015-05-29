#include "Descriptor.h"

Descriptor::Descriptor() : xml(NULL)
{

}

Descriptor::Descriptor(uint8_t* data) 
    : tag(data[0]), 
      length(data[1]),
      xml(NULL)
{
}


Descriptor::~Descriptor()
{

}

//##ModelId=5555699A0028
void Descriptor::resolved()
{
    xml = new TiXmlElement("unknow_descriptor");
    xml->SetAttribute("descriptor_tag", tag);

    TiXmlElement* tmp;
    char arr[16] = {0};
    sprintf(arr, "0x%x", tag);
    tmp = new TiXmlElement("descriptor_tag");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", length);
    tmp = new TiXmlElement("descriptor_length");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);
}

