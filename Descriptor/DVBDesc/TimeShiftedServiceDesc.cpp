#include "TimeShiftedServiceDesc.h"

//##ModelId=555AA88C0048
TimeShiftedServiceDesc::TimeShiftedServiceDesc()
{
}

//##ModelId=555AA89803A0
TimeShiftedServiceDesc::TimeShiftedServiceDesc(uint8_t* data)
    : Descriptor(data),
      reference_service_id((data[2] << 8) | data[3])
{
}

//##ModelId=555AA8D302D2
TimeShiftedServiceDesc::~TimeShiftedServiceDesc()
{
}

