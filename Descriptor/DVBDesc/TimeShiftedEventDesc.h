#ifndef TIMESHIFTEDEVENTDESC_H_HEADER_INCLUDED_AAA56BA2
#define TIMESHIFTEDEVENTDESC_H_HEADER_INCLUDED_AAA56BA2
#include "../Descriptor.h"

//descriptor_tag = 0x4E
//##ModelId=555AD8F10053
class TimeShiftedEventDesc : public Descriptor
{
  public:
    //##ModelId=555AD94A02BE
    TimeShiftedEventDesc();

    //##ModelId=555AD956036F
    TimeShiftedEventDesc(uint8_t* data);

    //##ModelId=555AD97400BF
    ~TimeShiftedEventDesc();

    //##ModelId=555AD9150338
    uint16_t reference_service_id;
    //##ModelId=555AD92A0198
    uint16_t reference_event_id;
};



#endif /* TIMESHIFTEDEVENTDESC_H_HEADER_INCLUDED_AAA56BA2 */
