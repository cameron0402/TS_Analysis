#include "Section.h"
#include "../TSAnalysis/TSFactory.h"

Section::Section(uint8_t* data, uint16_t len, uint32_t crc)
    : table_id(data[0]),
      syntax_indicator(data[1] >> 7),
      private_indicator((data[1] >> 6) & 0x01),
      length((data[1] & 0x0F) << 8 | data[2]),
      xml(NULL)
{
    raw_data = new uint8_t[len];
    memcpy(raw_data, data, len);
}

Section::~Section()
{
    if(xml != NULL)
    {
        delete xml;
        xml = NULL;
    }

    if(raw_data != NULL)
        delete []raw_data;
}

//##ModelId=5555540B00A0
bool Section::joinTo(TSFactory* sf)
{
    return false;
}

void Section::getDetail()
{

}

//##ModelId=555561E1025F
void Section::resolved()
{
    if(xml != NULL)
    {
        delete xml;
        xml = NULL;
    }

    xml = new TiXmlElement("Section");
    
    TiXmlElement* tmp;
    char arr[16] = {0};
    sprintf(arr, "0x%x", table_id);
    tmp = new TiXmlElement("table_id");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", syntax_indicator);
    tmp = new TiXmlElement("section_syntax_indicator");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", length);
    tmp = new TiXmlElement("section_length");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);
}


