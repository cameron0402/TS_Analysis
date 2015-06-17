#ifndef _SERVICE_GATEWAY_INFO_H_
#define _SERVICE_GATEWAY_INFO_H_

#include "IOP_IOR.h"

class ServiceGatewayInfo
{
public:
    ServiceGatewayInfo();
    ServiceGatewayInfo(uint8_t* data);
    virtual ~ServiceGatewayInfo();

    IOP_IOR* iop_ior;
    uint8_t download_taps_count;
    uint8_t service_context_list_count;
    uint16_t user_info_length;
    uint8_t* user_data;
};

#endif