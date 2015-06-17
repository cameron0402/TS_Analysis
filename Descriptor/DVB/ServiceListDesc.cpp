#include "ServiceListDesc.h"

ServiceListDesc::ServiceInfo::ServiceInfo()
{

}

ServiceListDesc::ServiceInfo::ServiceInfo(uint8_t* data)
    : service_id((data[0] << 8) | data[1]),
      service_type(data[2])
{
}

ServiceListDesc::ServiceInfo::~ServiceInfo()
{

}

//##ModelId=555982E400ED
ServiceListDesc::ServiceListDesc()
{
}

//##ModelId=555982EF00FD
ServiceListDesc::ServiceListDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    while(index < length + 2)
    {
        ServiceInfo* tmp = new ServiceInfo(data + index);
        service_list.push_back(tmp);
        index += 3;
    }
}

//##ModelId=5559831700ED
ServiceListDesc::~ServiceListDesc()
{
    std::list<ServiceInfo*>::iterator sit;
    for(sit = service_list.begin(); sit != service_list.end(); ++sit)
    {
        delete (*sit);
    }
    service_list.clear();
}

void ServiceListDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("service_list_descriptor");

    if(!service_list.empty())
    {
        std::list<ServiceInfo*>::iterator sit;
        for(sit = service_list.begin(); sit != service_list.end(); ++sit)
        {
            tmp = new TiXmlElement("Service");

            sprintf(arr, "0x%x", (*sit)->service_id);
            TiXmlElement* tms = new TiXmlElement("service_id");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*sit)->service_type);
            tms = new TiXmlElement("service_type");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            xml->LinkEndChild(tmp);
        }
        
    }
}

