#include "TDT.h"
#include "SectionFactory.h"

//##ModelId=556406A303DC
TDT::TDT()
{
}

//##ModelId=556406A801F1
TDT::TDT(uint8_t* data, uint16_t len, uint32_t crc)
    : Section(data, len),
      UTC_time()
{
    memcpy(UTC_time, data + 3, 5);
}

//##ModelId=556406AC01FA
TDT::~TDT()
{
}

bool TDT::joinTo(SectionFactory* sf)
{
    if(sf->tdt != NULL)
        return false;
    
    sf->tdt = this;
    return true;
}

void TDT::resolved()
{
    TiXmlElement* tmp;
    char arr[32] = {0};

    Section::resolved();
    xml->SetAttribute("table_id", table_id);

    utc_to_ymdhms(UTC_time, arr);
    tmp = new TiXmlElement("UTC_time");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);
}

