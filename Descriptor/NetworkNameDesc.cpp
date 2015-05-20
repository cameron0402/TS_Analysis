#include "NetworkNameDesc.h"

//##ModelId=55597F480343
NetworkNameDesc::NetworkNameDesc()
{
}

//##ModelId=55597F5400B9
NetworkNameDesc::NetworkNameDesc(uint8_t* data) : Descriptor(data)
{
    network_name = new uint8_t[length];
    memcpy(network_name, data + 2, length);
}

//##ModelId=55597F7A01E2
NetworkNameDesc::~NetworkNameDesc()
{
    delete []network_name;
}

