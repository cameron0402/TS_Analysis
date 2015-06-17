#include "DSI.h"

DSI::DSI()
{

}

DSI::DSI(uint8_t* data)
    : dsmh(new DsmccMessageHeader(data)),
      compatibility(0),
      private_data_length((data[34 + dsmh->adaptation_length] << 8) | data[35 + dsmh->adaptation_length])
{
    memset(serverID, 0xFF, 20);
    sgif = new ServiceGatewayInfo(data + 36 + dsmh->adaptation_length);
}

DSI::~DSI()
{
    if(sgif != NULL)
        delete sgif;
}