#ifndef ADAPTATIONFIELDDATADESC_H_HEADER_INCLUDED_AAA2C994
#define ADAPTATIONFIELDDATADESC_H_HEADER_INCLUDED_AAA2C994
#include "Descriptor.h"

// descriptor_tag = 0x70
//##ModelId=555D3A7B023F
class AdaptationFieldDataDesc : public Descriptor
{
  public:
    //##ModelId=555D3AA302E8
    AdaptationFieldDataDesc();

    //##ModelId=555D3AA501DC
    AdaptationFieldDataDesc(uint8_t* data);

    //##ModelId=555D3AA6039F
    virtual ~AdaptationFieldDataDesc();

    //##ModelId=555D3AD20360
    uint8_t adaptation_field_data_identifier;
};



#endif /* ADAPTATIONFIELDDATADESC_H_HEADER_INCLUDED_AAA2C994 */
