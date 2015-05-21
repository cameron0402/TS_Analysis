#include "AdaptationFieldDataDesc.h"

//##ModelId=555D3AA302E8
AdaptationFieldDataDesc::AdaptationFieldDataDesc()
{
}

//##ModelId=555D3AA501DC
AdaptationFieldDataDesc::AdaptationFieldDataDesc(uint8_t* data)
    : Descriptor(data),
      adaptation_field_data_identifier(data[2])
{
}

//##ModelId=555D3AA6039F
AdaptationFieldDataDesc::~AdaptationFieldDataDesc()
{
}

