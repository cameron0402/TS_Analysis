#include "CountryAvailabilityDesc.h"

//##ModelId=555A95ED0372
CountryAvailabilityDesc::CountryAvailabilityDesc()
{
}

//##ModelId=555A962C00F3
CountryAvailabilityDesc::CountryAvailabilityDesc(uint8_t* data)
    : Descriptor(data),
      country_availability_flag(data[2] >> 7)
{
    CountryCode tmp;
    int index = 3;
    while(index < length + 2)
    {
        memcpy(tmp.country_code, data + index, 3);
        country_list.push_back(tmp);
        index += 3;
    }
}

//##ModelId=555A967A0223
CountryAvailabilityDesc::~CountryAvailabilityDesc()
{
}

