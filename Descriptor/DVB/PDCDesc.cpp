#include "PDCDesc.h"

//##ModelId=555C4371031B
PDCDesc::PDCDesc()
{
}

//##ModelId=555C43740055
PDCDesc::PDCDesc(uint8_t* data) 
    : Descriptor(data),
      programme_identification_label(((data[2] & 0x0F) << 16) | (data[3] << 8) | data[4])
{
}

//##ModelId=555C4376020A
PDCDesc::~PDCDesc()
{
}

