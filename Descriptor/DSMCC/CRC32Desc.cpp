#include "CRC32Desc.h"

CRC32Desc::CRC32Desc()
{

}

CRC32Desc::CRC32Desc(uint8_t* data)
    : Descriptor(data),
      crc32((data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5])
{

}

CRC32Desc::~CRC32Desc()
{

}