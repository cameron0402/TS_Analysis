#include "CADesc.h"

//##ModelId=55583A9E026C
CADesc::CADesc()
{
}

//##ModelId=55583AA70125
CADesc::CADesc(uint8_t* data) 
    : Descriptor(data),
      CA_system_ID(data[2] << 8 | data[3]),
      CA_PID((data[4] & 0x1F) << 8 | data[5])
{
    private_data = new uint8_t[length - 4];
    memcpy(private_data, data + 6, length - 4);
}

//##ModelId=55583AC803BC
CADesc::~CADesc()
{
    delete []private_data;
}

void CADesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("CA_descriptor");

    sprintf(arr, "0x%x", CA_system_ID);
    tmp = new TiXmlElement("CA_system_ID");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", CA_PID);
    tmp = new TiXmlElement("CA_PID");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);
}

