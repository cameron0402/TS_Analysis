#include "MultilingualNetworkNameDesc.h"

MultilingualNetworkNameDesc::MultilingualNetworkNameDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2; 
    MNameInfo* mi;
    while(index < length + 2)
    {
       mi = new MNameInfo(data + index);
       index += 4 + mi->network_name_length;
       netname_list.push_back(mi);
    }
}

MultilingualNetworkNameDesc::~MultilingualNetworkNameDesc()
{
    std::list<MNameInfo*>::iterator mit;
    for(mit = netname_list.begin(); mit != netname_list.end(); ++mit)
    {
        delete (*mit);
    }
    netname_list.clear();
}

MultilingualNetworkNameDesc::MNameInfo::MNameInfo(uint8_t* data) 
    : ISO6392_language(),
      network_name_length(data[3])
{
    memcpy(ISO6392_language, data, 3);
    network_name = new uint8_t[network_name_length + 1];
    network_name[network_name_length] = 0;
    memcpy(network_name, data + 4, network_name_length);
}

MultilingualNetworkNameDesc::MNameInfo::MNameInfo(const MNameInfo& mnif)
{
    if(&mnif == this)
        return ;
    memcpy(ISO6392_language, mnif.ISO6392_language, 3);
    network_name_length = mnif.network_name_length;
    network_name = new uint8_t[network_name_length];
    memcpy(network_name, mnif.network_name, network_name_length);
}

MultilingualNetworkNameDesc::MNameInfo::~MNameInfo()
{
    delete []network_name;
}

void MultilingualNetworkNameDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("multilingual_network_name_descriptor");

    if(!netname_list.empty())
    {
        std::list<MNameInfo*>::iterator mit;
        for(mit = netname_list.begin(); mit != netname_list.end(); ++mit)
        {
            tmp = new TiXmlElement("Network-Name");

            TiXmlElement* tms = new TiXmlElement("ISO_639_2_language_code");
            arr[0] = (*mit)->ISO6392_language[0];
            arr[1] = (*mit)->ISO6392_language[1];
            arr[2] = (*mit)->ISO6392_language[2];
            arr[3] = 0;
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*mit)->network_name_length);
            tms = new TiXmlElement("network_name_length");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            tms = new TiXmlElement("network_name");
            tms->LinkEndChild(new TiXmlText((const char*)(*mit)->network_name));
            tmp->LinkEndChild(tms);

            xml->LinkEndChild(tmp);
        }
    }
}
