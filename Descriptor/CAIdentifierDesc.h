#ifndef CAIDENTIFIERDESC_H_HEADER_INCLUDED_AAA55D05
#define CAIDENTIFIERDESC_H_HEADER_INCLUDED_AAA55D05
#include "Descriptor.h"

//descriptor_tag = 0x53
//##ModelId=555AF4EF02C9
class CAIdentifierDesc : public Descriptor
{
  public:
    //##ModelId=555AF5260307
    CAIdentifierDesc();

    //##ModelId=555AF5300236
    CAIdentifierDesc(uint8_t* data);

    //##ModelId=555AF54802F5
    virtual ~CAIdentifierDesc();

    //##ModelId=555AF50C035D
    std::list<uint16_t> CA_id_list;
};



#endif /* CAIDENTIFIERDESC_H_HEADER_INCLUDED_AAA55D05 */
