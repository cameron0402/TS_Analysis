#include "ServiceDesc.h"

//##ModelId=555A8EC10111
ServiceDesc::ServiceDesc()
{
}

//##ModelId=555A8EC70294
ServiceDesc::ServiceDesc(uint8_t* data)
    : Descriptor(data),
      service_type(data[2]),
      service_provider_length(data[3]),
      service_name_length(data[4 + service_provider_length])
{
    service_provider = new uint8_t[service_provider_length + 1];
    service_provider[service_provider_length] = 0;
    memcpy(service_provider, data + 4, service_provider_length);

    service_name = new uint8_t[service_name_length + 1];
    service_name[service_name_length] = 0;
    memcpy(service_name, data + 5 + service_provider_length, service_name_length);

}

//##ModelId=555A8EE702F1
ServiceDesc::~ServiceDesc()
{
    delete []service_name;
    delete []service_provider;
}

void ServiceDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("service_descriptor");

    sprintf(arr, "0x%x", service_type);
    tmp = new TiXmlElement("service_type");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", service_provider_length);
    tmp = new TiXmlElement("service_provider_length");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    tmp = new TiXmlElement("service_provider");
    tmp->LinkEndChild(new TiXmlText((const char*)service_provider));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", service_name_length);
    tmp = new TiXmlElement("service_name_length");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    tmp = new TiXmlElement("service_name");
    tmp->LinkEndChild(new TiXmlText((const char*)service_name));
    xml->LinkEndChild(tmp);
}

