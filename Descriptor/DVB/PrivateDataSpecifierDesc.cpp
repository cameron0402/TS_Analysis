#include "PrivateDataSpecifierDesc.h"

PrivateDataSpecifierDesc::PrivateDataSpecifierDesc(uint8_t* data)
    : Descriptor(data),
      private_data_specifier((data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5])
{
}

PrivateDataSpecifierDesc::~PrivateDataSpecifierDesc()
{
}

