#include "ServiceMoveDesc.h"

//##ModelId=555C2E320366
ServiceMoveDesc::ServiceMoveDesc()
{
}

//##ModelId=555C2E38018D
ServiceMoveDesc::ServiceMoveDesc(uint8_t* data)
    : Descriptor(data),
      new_original_network_id((data[2] << 8) | data[3]),
      new_transport_stream_id((data[4] << 8) | data[5]),
      new_service_id((data[6] << 8) | data[7])
{
}

//##ModelId=555C2E3B0026
ServiceMoveDesc::~ServiceMoveDesc()
{
}

