#ifndef _INFO_DESC_H_
#define _INFO_DESC_H_

#include "../Descriptor.h"

//descriptor_tag = 0x03
class InfoDesc : public Descriptor
{
public:
    InfoDesc();
    InfoDesc(uint8_t* data);
    virtual ~InfoDesc();

    uint8_t ISO_639_language[3];
    uint8_t* info;
};

#endif