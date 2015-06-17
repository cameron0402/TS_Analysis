#include "CompressModuleDesc.h"

CompressModuleDesc::CompressModuleDesc()
{

}

CompressModuleDesc::CompressModuleDesc(uint8_t* data)
    : Descriptor(data),
      compression_method(data[2]),
      original_size((data[3] << 24) | (data[4] << 16) | (data[5] << 8) | data[6])
{

}

CompressModuleDesc::~CompressModuleDesc()
{

}