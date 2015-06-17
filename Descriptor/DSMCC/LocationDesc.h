#ifndef _LOCATION_DESC_H_
#define _LOCATION_DESC_H_

#include "../Descriptor.h"

//descriptor_tag = 0x06
class LocationDesc : public Descriptor
{
public:
    LocationDesc();
    LocationDesc(uint8_t* data);
    virtual ~LocationDesc();

    uint8_t location_tag;
};

#endif