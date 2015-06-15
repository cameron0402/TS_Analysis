#ifndef SYSTEMCLOCKDESC_H_HEADER_INCLUDED_AAA6E98C
#define SYSTEMCLOCKDESC_H_HEADER_INCLUDED_AAA6E98C
#include "../Descriptor.h"

//descriptor_tag = 0x0B
//##ModelId=5559448001D1
class SystemClockDesc : public Descriptor
{
  public:
    //##ModelId=5559450E0114
    SystemClockDesc();

    //##ModelId=5559451802B5
    SystemClockDesc(uint8_t* data);

    //##ModelId=55594540019D
    virtual ~SystemClockDesc();

    //##ModelId=555944A903C4
    bool external_clock_reference_indicator;
    //##ModelId=555944CA02BD
    uint8_t clock_accuracy_integer;
    //##ModelId=555944E5037E
    uint8_t clock_accuracy_exponent;
};



#endif /* SYSTEMCLOCKDESC_H_HEADER_INCLUDED_AAA6E98C */
