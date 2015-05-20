#include "MultiplexBufferUtilizationDesc.h"

//##ModelId=55594A2B0077
MultiplexBufferUtilizationDesc::MultiplexBufferUtilizationDesc()
{
}

//##ModelId=55594A410077
MultiplexBufferUtilizationDesc::MultiplexBufferUtilizationDesc(uint8_t* data) 
    : Descriptor(data),
      mdv_valid_flag(data[2] >> 7),
      multiplex_delay_variation((data[2] & 0x7F) << 8 | data[3]),
      multiplex_strategy(data[4] >> 5)
{
}

//##ModelId=55594A6B0286
MultiplexBufferUtilizationDesc::~MultiplexBufferUtilizationDesc()
{
}

