#include "SatelliteDeliverySystemDesc.h"

//##ModelId=555987F0000D
SatelliteDeliverySystemDesc::SatelliteDeliverySystemDesc()
{
}

//##ModelId=555987FE00D8
SatelliteDeliverySystemDesc::SatelliteDeliverySystemDesc(uint8_t* data) 
    : Descriptor(data),
      frequency((data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5]),
      orbital_position((data[6] << 8) | data[7]),
      west_east_flag(data[8] >> 7),
      polarization((data[8] >> 5) & 0x03),
      modulation(data[8] & 0x1F),
      symbol_rate((data[9] << 20) | (data[10] << 12) | (data[11] << 4) | (data[12] >> 4)),
      FEC_inner(data[12] & 0x0F)
{
}

//##ModelId=55598855000C
SatelliteDeliverySystemDesc::~SatelliteDeliverySystemDesc()
{
}

