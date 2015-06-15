#ifndef SATELLITEDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA66BA5
#define SATELLITEDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA66BA5
#include "../Descriptor.h"

//descriptor_tag = 0x43
//##ModelId=55598716032A
class SatelliteDeliverySystemDesc : public Descriptor
{
  public:
    //##ModelId=555987F0000D
    SatelliteDeliverySystemDesc();

    //##ModelId=555987FE00D8
    SatelliteDeliverySystemDesc(uint8_t* data);

    //##ModelId=55598855000C
    virtual ~SatelliteDeliverySystemDesc();

    //##ModelId=5559874103BB
    uint32_t frequency;
    //##ModelId=555987570092
    uint16_t orbital_position;
    //##ModelId=5559877A03A3
    bool west_east_flag;
    //##ModelId=5559879401DC
    uint32_t polarization;
    //##ModelId=555987AF02FC
    uint8_t modulation;
    //##ModelId=555987C201F2
    uint32_t symbol_rate;
    //##ModelId=555987D60024
    uint8_t FEC_inner;
};



#endif /* SATELLITEDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA66BA5 */
