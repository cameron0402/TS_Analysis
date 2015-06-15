#ifndef _COMPRESS_MODULE_DESC_
#define _COMPRESS_MODULE_DESC_

#include "../Descriptor.h"

//descriptor_tag = 0x09
class CompressModuleDesc : public Descriptor
{
public:
    CompressModuleDesc();
    CompressModuleDesc(uint8_t* data);
    virtual ~CompressModuleDesc();

    uint8_t compression_method;
    uint32_t original_size;
};

#endif