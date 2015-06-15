#ifndef DTSAUDIOSTREAMDESC_H_HEADER_INCLUDED_AAA2CD75
#define DTSAUDIOSTREAMDESC_H_HEADER_INCLUDED_AAA2CD75
#include "../Descriptor.h"

//descriptor_tag = 0x7B
//##ModelId=555D43CB026D
class DTSAudioStreamDesc : public Descriptor
{
  public:
    //##ModelId=555D43EF01FD
    DTSAudioStreamDesc();

    //##ModelId=555D43F101BB
    DTSAudioStreamDesc(uint8_t* data);

    //##ModelId=555D43F3012C
    virtual ~DTSAudioStreamDesc();

    //##ModelId=555D44150175
    uint8_t sample_rate_code;
    //##ModelId=555D442E029A
    uint8_t bit_rate_code;
    //##ModelId=555D4442023E
    uint8_t nblks;
    //##ModelId=555D4454039A
    uint8_t fsize;
    //##ModelId=555D44650133
    uint8_t surround_mode;
    //##ModelId=555D447D0112
    bool ife_flag;
    //##ModelId=555D448F025D
    uint8_t extended_surround_flag;
    //##ModelId=555D44A90091
    uint8_t* add_info;
};



#endif /* DTSAUDIOSTREAMDESC_H_HEADER_INCLUDED_AAA2CD75 */
