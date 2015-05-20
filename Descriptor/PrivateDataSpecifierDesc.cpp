#include "PrivateDataSpecifierDesc.h"

//##ModelId=555C2AC1014E
PrivateDataSpecifierDesc::PrivateDataSpecifierDesc()
{
}

//##ModelId=555C2AC303E1
PrivateDataSpecifierDesc::PrivateDataSpecifierDesc(uint8_t* data)
    : Descriptor(data),
      private_data_specifier((data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5])
{
}

//##ModelId=555C2AC601F5
PrivateDataSpecifierDesc::~PrivateDataSpecifierDesc()
{
}

