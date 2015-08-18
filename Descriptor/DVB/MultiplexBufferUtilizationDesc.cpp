#include "MultiplexBufferUtilizationDesc.h"

MultiplexBufferUtilizationDesc::MultiplexBufferUtilizationDesc(uint8_t* data) 
    : Descriptor(data),
      mdv_valid_flag(data[2] >> 7),
      multiplex_delay_variation((data[2] & 0x7F) << 8 | data[3]),
      multiplex_strategy(data[4] >> 5)
{
}

MultiplexBufferUtilizationDesc::~MultiplexBufferUtilizationDesc()
{
}

