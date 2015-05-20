#ifndef COPYRIGHTDESC_H_HEADER_INCLUDED_AAA6D6D9
#define COPYRIGHTDESC_H_HEADER_INCLUDED_AAA6D6D9
#include "Descriptor.h"

// descriptor_tag = 0x0D
//##ModelId=55594BF50169
class CopyrightDesc : public Descriptor
{
  public:
    //##ModelId=55594C8E0036
    CopyrightDesc();

    //##ModelId=55594C9502C6
    CopyrightDesc(uint8_t* data);

    //##ModelId=55594CBF0307
    virtual ~CopyrightDesc();

    //##ModelId=55594C420098
    uint32_t copyright_identifier;
    //##ModelId=55594C590239
    uint8_t* additional_copyright_info;
};



#endif /* COPYRIGHTDESC_H_HEADER_INCLUDED_AAA6D6D9 */
