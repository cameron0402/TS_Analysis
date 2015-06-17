#ifndef STDDESC_H_HEADER_INCLUDED_AAA6DCC0
#define STDDESC_H_HEADER_INCLUDED_AAA6DCC0
#include "../Descriptor.h"

//descriptor_tag = 0x11
//##ModelId=555975F9027C
class STDDesc : public Descriptor
{
  public:
    //##ModelId=5559763403B0
    STDDesc();

    //##ModelId=5559763B0306
    STDDesc(uint8_t* data);

    //##ModelId=555976680250
    virtual ~STDDesc();

    //##ModelId=5559761E0151
    bool leak_valid_flag;
};



#endif /* STDDESC_H_HEADER_INCLUDED_AAA6DCC0 */
