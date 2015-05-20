#include "MultilingualNetworkNameDesc.h"

//##ModelId=555C035401E5
MultilingualNetworkNameDesc::MultilingualNetworkNameDesc()
{
}

//##ModelId=555C03570297
MultilingualNetworkNameDesc::MultilingualNetworkNameDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2; 
    while(index < length + 2)
    {
        MNameInfo tmp;
        memcpy(tmp.ISO6392_language, data + index, 3);
        tmp.network_name_length = data[index + 4];
        tmp.network_name = new uint8_t[tmp.network_name_length];
        memcpy(tmp.network_name, data + 5 + index, tmp.network_name_length);
        index += 5 + tmp.network_name_length;
        netname_list.push_back(tmp);
    }
}

//##ModelId=555C036901A6
MultilingualNetworkNameDesc::~MultilingualNetworkNameDesc()
{
}

MultilingualNetworkNameDesc::MNameInfo::MNameInfo()
{
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

