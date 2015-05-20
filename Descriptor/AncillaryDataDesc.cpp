#include "AncillaryDataDesc.h"

//##ModelId=555C4B680085
AncillaryDataDesc::AncillaryDataDesc()
{
}

//##ModelId=555C4B6903C4
AncillaryDataDesc::AncillaryDataDesc(uint8_t* data)
    : Descriptor(data),
      ancillary_data_identifier(data[2])
{
}

//##ModelId=555C4B6B0384
AncillaryDataDesc::~AncillaryDataDesc()
{
}

