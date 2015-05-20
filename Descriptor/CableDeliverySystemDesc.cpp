#include "CableDeliverySystemDesc.h"

//##ModelId=55599A2F0339
CableDeliverySystemDesc::CableDeliverySystemDesc()
{
}

//##ModelId=55599A3D00E1
CableDeliverySystemDesc::CableDeliverySystemDesc(uint8_t* data) 
    : Descriptor(data),
      frequency((data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5]),
      FEC_outer(data[7] & 0x0F),
      modulation(data[8]),
      symbol_rate((data[9] << 20) | (data[10] << 12) | (data[11] << 4) | (data[12] >> 4)),
      FEC_inner(data[12] & 0x0F)
{
}

//##ModelId=55599A59017E
CableDeliverySystemDesc::~CableDeliverySystemDesc()
{
}

