#ifndef FREQUENCYLISTDESC_H_HEADER_INCLUDED_AAA384E9
#define FREQUENCYLISTDESC_H_HEADER_INCLUDED_AAA384E9
#include "Descriptor.h"

//descriptor_tag = 0x62
//##ModelId=555C37630273
class FrequencyListDesc : public Descriptor
{
  public:
    //##ModelId=555C37790301
    FrequencyListDesc();

    //##ModelId=555C377C003F
    FrequencyListDesc(uint8_t* data);

    //##ModelId=555C377E008F
    virtual ~FrequencyListDesc();

    //##ModelId=555C37BA0041
    uint8_t coding_type;
    //##ModelId=555C37CC02D3
    std::list<uint32_t> centre_freq_list;
};



#endif /* FREQUENCYLISTDESC_H_HEADER_INCLUDED_AAA384E9 */
