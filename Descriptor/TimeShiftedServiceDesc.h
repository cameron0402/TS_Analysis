#ifndef TIMESHIFTEDSERVICEDESC_H_HEADER_INCLUDED_AAA5366A
#define TIMESHIFTEDSERVICEDESC_H_HEADER_INCLUDED_AAA5366A
#include "Descriptor.h"

//descriptor_tag = 0x4C
//##ModelId=555AA855028C
class TimeShiftedServiceDesc : public Descriptor
{
  public:
    //##ModelId=555AA88C0048
    TimeShiftedServiceDesc();

    //##ModelId=555AA89803A0
    TimeShiftedServiceDesc(uint8_t* data);

    //##ModelId=555AA8D302D2
    virtual ~TimeShiftedServiceDesc();

    //##ModelId=555AA8740017
    uint16_t reference_service_id;
};



#endif /* TIMESHIFTEDSERVICEDESC_H_HEADER_INCLUDED_AAA5366A */
