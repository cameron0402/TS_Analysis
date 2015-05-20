#include "LinkageDesc.h"

//##ModelId=555AA14C000F
LinkageDesc::LinkageDesc()
{
}

//##ModelId=555AA155006E
LinkageDesc::LinkageDesc(uint8_t* data)
    : Descriptor(data),
      transport_stream_id((data[2] << 8) | data[3]),
      original_network_id((data[4] << 8) | data[5]),
      service_id((data[6] << 8) | data[7]),
      linkage_type(data[8])
{
    if(linkage_type == 0x08)
    {
        hand_over_type = data[9] >> 4;
        origin_type = data[9] & 0x1;
        int index = 10;
        if(hand_over_type >= 0x1 && hand_over_type <= 0x3)
        {
            network_id = (data[index] << 8) | data[index + 1];
            index += 2;
        }
        if(origin_type == 0x0)
        {
            initial_service_id = (data[index] << 8) | data[index + 1];
            index += 2;
        }    
    }
}

//##ModelId=555AA16F024C
LinkageDesc::~LinkageDesc()
{
}

