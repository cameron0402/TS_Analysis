#ifndef _DSI_H_
#define _DSI_H_

#include "DsmccMessageHeader.h"
#include "ServiceGatewayInfo.h"

class DSI
{
public:
    DSI();
    DSI(uint8_t* data);
    virtual ~DSI();

    DsmccMessageHeader* dsmh;
    uint8_t serverID[20];
    uint16_t compatibility;
    uint16_t private_data_length;
    ServiceGatewayInfo* sgif;
};

#endif 