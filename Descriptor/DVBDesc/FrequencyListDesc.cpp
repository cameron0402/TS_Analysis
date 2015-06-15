#include "FrequencyListDesc.h"

//##ModelId=555C37790301
FrequencyListDesc::FrequencyListDesc()
{
}

//##ModelId=555C377C003F
FrequencyListDesc::FrequencyListDesc(uint8_t* data)
    : Descriptor(data),
      coding_type(data[2] & 0x03)
{
    int index = 3;
    while(index < length + 2)
    {
        centre_freq_list.push_back((data[index] << 24) | (data[index + 1] << 16) | (data[index + 2] << 8) | (data[index + 3]));
        index += 4;
    }
}

//##ModelId=555C377E008F
FrequencyListDesc::~FrequencyListDesc()
{
}

