#ifndef PDCDESC_H_HEADER_INCLUDED_AAA386B7
#define PDCDESC_H_HEADER_INCLUDED_AAA386B7
#include "Descriptor.h"

//descriptor_tag = 0x69
//##ModelId=555C4363030F
class PDCDesc : public Descriptor
{
  public:
    //##ModelId=555C4371031B
    PDCDesc();

    //##ModelId=555C43740055
    PDCDesc(uint8_t* data);

    //##ModelId=555C4376020A
    virtual ~PDCDesc();

    //##ModelId=555C439E012D
    uint32_t programme_identification_label;
};



#endif /* PDCDESC_H_HEADER_INCLUDED_AAA386B7 */
