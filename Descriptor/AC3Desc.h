#ifndef AC3DESC_H_HEADER_INCLUDED_AAA3B6CD
#define AC3DESC_H_HEADER_INCLUDED_AAA3B6CD
#include "Descriptor.h"

//descriptor_tag = 0x6A
//##ModelId=555C46DF0054
class AC3Desc : public Descriptor
{
  public:
    //##ModelId=555C46F500D3
    AC3Desc();

    //##ModelId=555C46F70063
    AC3Desc(uint8_t* data);

    //##ModelId=555C46F900CC
    virtual ~AC3Desc();

    //##ModelId=555C47230233
    bool component_type_flag;
    //##ModelId=555C474202C4
    bool bsid_flag;
    //##ModelId=555C475002B3
    bool mainid_flag;
    //##ModelId=555C476001FE
    bool asvc_flag;
    //##ModelId=555C4777011A
    uint8_t component_type;
    //##ModelId=555C479A021C
    uint8_t bsid;
    //##ModelId=555C47A7038C
    uint8_t mainid;
    //##ModelId=555C47B703BB
    uint8_t asvc;
    //##ModelId=555C47C80183
    uint8_t* add_info;
};



#endif /* AC3DESC_H_HEADER_INCLUDED_AAA3B6CD */
