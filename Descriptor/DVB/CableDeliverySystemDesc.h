#ifndef CABLEDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA637AB
#define CABLEDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA637AB
#include "../Descriptor.h"

//descriptor_tag = 0x44
//##ModelId=5559999C030F
class CableDeliverySystemDesc : public Descriptor
{
  public:
    //##ModelId=55599A2F0339
    CableDeliverySystemDesc();

    //##ModelId=55599A3D00E1
    CableDeliverySystemDesc(uint8_t* data);

    //##ModelId=55599A59017E
    virtual ~CableDeliverySystemDesc();
    virtual void resolved();

    //##ModelId=555999C202E1
    uint32_t frequency;
    //##ModelId=555999D500D3
    uint8_t FEC_outer;
    //##ModelId=555999E9005B
    uint8_t modulation;
    //##ModelId=555999FC0382
    uint32_t symbol_rate;
    //##ModelId=55599A16021C
    uint8_t FEC_inner;
};



#endif /* CABLEDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA637AB */
