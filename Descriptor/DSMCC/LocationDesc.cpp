#include "LocationDesc.h"

LocationDesc::LocationDesc()
{

}

LocationDesc::LocationDesc(uint8_t* data)
    : Descriptor(data),
      location_tag(data[2])
{

}

LocationDesc::~LocationDesc()
{

}