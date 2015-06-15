#ifndef IBPDESC_H_HEADER_INCLUDED_AAA6C70A
#define IBPDESC_H_HEADER_INCLUDED_AAA6C70A
#include "../Descriptor.h"

//descriptor_tag = 0x12
//##ModelId=5559778F01EF
class IBPDesc : public Descriptor
{
  public:
    //##ModelId=5559779B017B
    IBPDesc();

    //##ModelId=555977A00190
    IBPDesc(uint8_t* data);

    //##ModelId=555977CA0358
    virtual ~IBPDesc();

    //##ModelId=555977F60289
    bool closed_gop_flag;
    //##ModelId=5559780C00B2
    bool identical_gop_flag;
    //##ModelId=5559782B0020
    uint16_t max_gop_length;
};



#endif /* IBPDESC_H_HEADER_INCLUDED_AAA6C70A */
