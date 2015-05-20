#include "TerrestrialDeliverySystemDesc.h"

//##ModelId=555C00F90065
TerrestrialDeliverySystemDesc::TerrestrialDeliverySystemDesc()
{
}

//##ModelId=555C00FC01D5
TerrestrialDeliverySystemDesc::TerrestrialDeliverySystemDesc(uint8_t* data)
    : Descriptor(data),
      centre_frequency((data[2] << 24) | (data[3] << 16) | data[4] << 8 | data[5]),
      FEC(data[6] >> 4),
      modulation(data[6] & 0x0F),
      number_of_subcarrier(data[7] >> 4),
      frame_header_mode(data[7] & 0x0F),
      interleaving_mode(data[8] >> 4),
      other_frequency_flag((data[8] >> 3) & 0x01),
      sfn_mfn_flag((data[8] >> 2) & 0x01)
{
}

//##ModelId=555C00FF037E
TerrestrialDeliverySystemDesc::~TerrestrialDeliverySystemDesc()
{
}

