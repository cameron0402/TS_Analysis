#include "StreamIdentifierDesc.h"

//##ModelId=555AF0580055
StreamIdentifierDesc::StreamIdentifierDesc()
{
}

//##ModelId=555AF06F0115
StreamIdentifierDesc::StreamIdentifierDesc(uint8_t* data)
    : Descriptor(data),
      component_tag(data[2])
{
}

//##ModelId=555AF0800135
StreamIdentifierDesc::~StreamIdentifierDesc()
{
}

