#include "SystemClockDesc.h"

//##ModelId=5559450E0114
SystemClockDesc::SystemClockDesc()
{
}

//##ModelId=5559451802B5
SystemClockDesc::SystemClockDesc(uint8_t* data) 
    : Descriptor(data),
      external_clock_reference_indicator(data[2] >> 7),
      clock_accuracy_integer(data[2] & 0x3F),
      clock_accuracy_exponent(data[3] >> 5)
{
}

//##ModelId=55594540019D
SystemClockDesc::~SystemClockDesc()
{
}

