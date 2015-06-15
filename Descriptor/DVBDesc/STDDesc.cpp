#include "STDDesc.h"

//##ModelId=5559763403B0
STDDesc::STDDesc()
{
}

//##ModelId=5559763B0306
STDDesc::STDDesc(uint8_t* data) 
    : Descriptor(data),
      leak_valid_flag(data[2] & 0x01)
{
}

//##ModelId=555976680250
STDDesc::~STDDesc()
{
}

