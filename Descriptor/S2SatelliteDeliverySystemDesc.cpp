#include "S2SatelliteDeliverySystemDesc.h"

//##ModelId=555D3FAD0008
S2SatelliteDeliverySystemDesc::S2SatelliteDeliverySystemDesc()
{
}

//##ModelId=555D3FB30261
S2SatelliteDeliverySystemDesc::S2SatelliteDeliverySystemDesc(uint8_t* data)
    : Descriptor(data),
      scrambling_sequence_selector(data[2] >> 7),
      multiple_input_stream_flag((data[2] >> 6) & 0x01),
      backwards_compatibility_indicator((data[2] >> 5) & 0x01)
{
    int index = 3;
    if(scrambling_sequence_selector)
    {
        scrambling_sequence_index = ((data[index] & 0x03) << 16) | (data[index + 2] << 8) | data[index + 3];
        index += 3;
    }
    if(multiple_input_stream_flag)
    {
        input_stream_identifier = data[index];
    }
}

//##ModelId=555D3FB5024E
S2SatelliteDeliverySystemDesc::~S2SatelliteDeliverySystemDesc()
{
}

