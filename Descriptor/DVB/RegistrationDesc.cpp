#include "RegistrationDesc.h"

RegistrationDesc::RegistrationDesc(uint8_t* data) 
    : Descriptor(data),
      format_identifier((data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5])
{
    additional_identification_info = new uint8_t[length - 4];
    memcpy(additional_identification_info, data + 6, length - 4);
}

//##ModelId=555831EC01D2
RegistrationDesc::~RegistrationDesc()
{
    delete []additional_identification_info;
}

