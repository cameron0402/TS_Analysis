#ifndef PRIVATEDATAINDICATORDESC_H_HEADER_INCLUDED_AAA6CFFF
#define PRIVATEDATAINDICATORDESC_H_HEADER_INCLUDED_AAA6CFFF
#include "../Descriptor.h"

// descriptor_tag = 0x0F
//##ModelId=555950EB0105
class PrivateDataIndicatorDesc : public Descriptor
{
  public:
    //##ModelId=5559514A0010
    PrivateDataIndicatorDesc();

    //##ModelId=5559515B0187
    PrivateDataIndicatorDesc(uint8_t* data);

    //##ModelId=5559518102D7
    virtual ~PrivateDataIndicatorDesc();

    //##ModelId=5559510203B0
    uint32_t private_data_indicator;
};



#endif /* PRIVATEDATAINDICATORDESC_H_HEADER_INCLUDED_AAA6CFFF */
