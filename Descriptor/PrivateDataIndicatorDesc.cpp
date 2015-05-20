#include "PrivateDataIndicatorDesc.h"

//##ModelId=5559514A0010
PrivateDataIndicatorDesc::PrivateDataIndicatorDesc()
{
}

//##ModelId=5559515B0187
PrivateDataIndicatorDesc::PrivateDataIndicatorDesc(uint8_t* data) 
    : Descriptor(data),
      private_data_indicator((data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5])
{
}

//##ModelId=5559518102D7
PrivateDataIndicatorDesc::~PrivateDataIndicatorDesc()
{
}

