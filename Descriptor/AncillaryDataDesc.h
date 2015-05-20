#ifndef ANCILLARYDATADESC_H_HEADER_INCLUDED_AAA3E4FF
#define ANCILLARYDATADESC_H_HEADER_INCLUDED_AAA3E4FF
#include "Descriptor.h"

//descriptor_tag = 0x6B
//##ModelId=555C4B5602D6
class AncillaryDataDesc : public Descriptor
{
  public:
    //##ModelId=555C4B680085
    AncillaryDataDesc();

    //##ModelId=555C4B6903C4
    AncillaryDataDesc(uint8_t* data);

    //##ModelId=555C4B6B0384
    virtual ~AncillaryDataDesc();

    //##ModelId=555C4B84013C
    uint8_t ancillary_data_identifier;
};



#endif /* ANCILLARYDATADESC_H_HEADER_INCLUDED_AAA3E4FF */
