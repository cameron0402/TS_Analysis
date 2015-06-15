#include "NetworkNameDesc.h"

//##ModelId=55597F480343
NetworkNameDesc::NetworkNameDesc()
{
}

//##ModelId=55597F5400B9
NetworkNameDesc::NetworkNameDesc(uint8_t* data) : Descriptor(data)
{
    network_name = new uint8_t[length + 1];
    network_name[length] = 0;
    memcpy(network_name, data + 2, length);
}

//##ModelId=55597F7A01E2
NetworkNameDesc::~NetworkNameDesc()
{
    delete []network_name;
}

void NetworkNameDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("network_name_descriptor");

    tmp = new TiXmlElement("network_name");
    tmp->LinkEndChild(new TiXmlText((const char*)network_name));
    xml->LinkEndChild(tmp);
}

