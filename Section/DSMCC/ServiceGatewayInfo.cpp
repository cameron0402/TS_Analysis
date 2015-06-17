#include "ServiceGatewayInfo.h"

ServiceGatewayInfo::ServiceGatewayInfo()
{

}

ServiceGatewayInfo::ServiceGatewayInfo(uint8_t* data)
{
    iop_ior = new IOP_IOR(data);
    uint8_t* pd = data + iop_ior->iop_ior_length;
    download_taps_count = (pd[0]);
    service_context_list_count = (pd[1]);
    user_info_length = ((pd[2] << 8) | pd[3]);
    user_data = new uint8_t[user_info_length];
    memcpy(user_data, pd + 4, user_info_length);
}

ServiceGatewayInfo::~ServiceGatewayInfo()
{
    if(iop_ior != NULL)
        delete iop_ior;

    if(user_data != NULL)
        delete []user_data;
}