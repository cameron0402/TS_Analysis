#ifndef _CRC32_DESC_
#define _CRC32_DESC_

#include "../Descriptor.h"
///descriptor_tag = 0x05

class CRC32Desc : public Descriptor
{
public:
    CRC32Desc();
    CRC32Desc(uint8_t* data);
    virtual ~CRC32Desc();

    uint32_t crc32;
};

#endif