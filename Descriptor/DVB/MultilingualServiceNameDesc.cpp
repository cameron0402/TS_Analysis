#include "MultilingualServiceNameDesc.h"

MultilingualServiceNameDesc::ServiceInfo::ServiceInfo(const ServiceInfo& sif)
{
    if(&sif == this)
        return ;
    service_provider_name_length = sif.service_provider_name_length;
    service_provider_name = new uint8_t[service_provider_name_length];
    memcpy(service_provider_name, sif.service_provider_name, service_provider_name_length);

    service_name_length = sif.service_name_length;
    service_name = new uint8_t[service_name_length];
    memcpy(service_name, sif.service_name, service_name_length);
}

MultilingualServiceNameDesc::ServiceInfo::ServiceInfo(uint8_t* data)
    : ISO6392_language(),
      service_provider_name_length(data[3]),
      service_name_length(data[4 + service_provider_name_length])
{
    memcpy(ISO6392_language, data, 3);

    service_provider_name = new uint8_t[service_provider_name_length + 1];
    service_provider_name[service_provider_name_length] = 0;
    memcpy(service_provider_name, data + 4, service_provider_name_length);

    service_name = new uint8_t[service_name_length + 1];
    service_name[service_name_length] = 0;
    memcpy(service_name, data + 5 + service_provider_name_length, service_name_length);
}

MultilingualServiceNameDesc::ServiceInfo::~ServiceInfo()
{
    delete []service_provider_name;
    delete []service_name;
}

MultilingualServiceNameDesc::MultilingualServiceNameDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2; 
    ServiceInfo* si;
    while(index < length + 2)
    {
        si = new ServiceInfo(data + index);
        index += si->service_name_length + si->service_provider_name_length + 5;
        service_list.push_back(si);
    }
}

MultilingualServiceNameDesc::~MultilingualServiceNameDesc()
{
    std::list<ServiceInfo*>::iterator sit;
    for(sit = service_list.begin(); sit != service_list.end(); ++sit)
    {
        delete (*sit);
    }
    service_list.clear();
}

void MultilingualServiceNameDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[256] = {0};

    Descriptor::resolved();
    xml->SetValue("multilingual_service_name_descriptor");

    if(!service_list.empty())
    {
        std::list<ServiceInfo*>::iterator sit;
        for(sit = service_list.begin(); sit != service_list.end(); ++sit)
        {
            tmp = new TiXmlElement("Service_Info");

            memcpy(arr, (*sit)->ISO6392_language, 3);
            arr[3] = 0;
            TiXmlElement* tms = new TiXmlElement("ISO_639_2_language_code");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*sit)->service_provider_name_length);
            tms = new TiXmlElement("service_provider_name_length");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            if((*sit)->service_provider_name_length > 0)
            {
                coding_string_to_gb((*sit)->service_provider_name, (uint8_t*)arr, (*sit)->service_provider_name_length);
                tms = new TiXmlElement("service_provider_name");
                tms->LinkEndChild(new TiXmlText(arr));
                tmp->LinkEndChild(tms);
            }

            sprintf(arr, "0x%x", (*sit)->service_name_length);
            tms = new TiXmlElement("service_name_length");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            if((*sit)->service_name_length > 0)
            {
                coding_string_to_gb((*sit)->service_name, (uint8_t*)arr, (*sit)->service_name_length);
                tms = new TiXmlElement("service_name");
                tms->LinkEndChild(new TiXmlText(arr));
                tmp->LinkEndChild(tms);
            }
           
            xml->LinkEndChild(tmp);
        }
    }
}

