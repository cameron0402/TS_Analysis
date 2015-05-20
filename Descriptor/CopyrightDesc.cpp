#include "CopyrightDesc.h"

//##ModelId=55594C8E0036
CopyrightDesc::CopyrightDesc()
{
}

//##ModelId=55594C9502C6
CopyrightDesc::CopyrightDesc(uint8_t* data) 
    : Descriptor(data),
      copyright_identifier((data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5])
{
    additional_copyright_info = new uint8_t[length - 4];
    memcpy(additional_copyright_info, data + 6, length - 4);
}

//##ModelId=55594CBF0307
CopyrightDesc::~CopyrightDesc()
{
    delete []additional_copyright_info;
}

