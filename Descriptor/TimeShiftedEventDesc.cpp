#include "TimeShiftedEventDesc.h"

//##ModelId=555AD94A02BE
TimeShiftedEventDesc::TimeShiftedEventDesc()
{
}

//##ModelId=555AD956036F
TimeShiftedEventDesc::TimeShiftedEventDesc(uint8_t* data)
    : Descriptor(data),
      reference_service_id((data[2] << 8) | data[3]),
      reference_event_id((data[4] << 8) | data[5])
{
}

//##ModelId=555AD97400BF
TimeShiftedEventDesc::~TimeShiftedEventDesc()
{
}

