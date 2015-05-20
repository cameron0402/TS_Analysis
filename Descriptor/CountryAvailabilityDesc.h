#ifndef COUNTRYAVAILABILITYDESC_H_HEADER_INCLUDED_AAA55429
#define COUNTRYAVAILABILITYDESC_H_HEADER_INCLUDED_AAA55429
#include "Descriptor.h"

//descriptor_tag = 0x49
//##ModelId=555A945D0355
class CountryAvailabilityDesc : public Descriptor
{
  public:
    //##ModelId=555A957B0291
    class CountryCode
    {
      public:
        //##ModelId=555A958A0115
        uint8_t country_code[3];
    };

    //##ModelId=555A95ED0372
    CountryAvailabilityDesc();

    //##ModelId=555A962C00F3
    CountryAvailabilityDesc(uint8_t* data);

    //##ModelId=555A967A0223
    virtual ~CountryAvailabilityDesc();

    //##ModelId=555A95B30294
    bool country_availability_flag;
    //##ModelId=555A95CB034A
    std::list<CountryCode> country_list;
};



#endif /* COUNTRYAVAILABILITYDESC_H_HEADER_INCLUDED_AAA55429 */
