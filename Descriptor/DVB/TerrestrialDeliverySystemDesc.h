#ifndef TERRESTRIALDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA3896C
#define TERRESTRIALDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA3896C
#include "../Descriptor.h"

// descriptor_tag = 0x5A
//##ModelId=555BFFB50271
class TerrestrialDeliverySystemDesc : public Descriptor
{
  public:
    //##ModelId=555C00F90065
    TerrestrialDeliverySystemDesc();

    //##ModelId=555C00FC01D5
    TerrestrialDeliverySystemDesc(uint8_t* data);

    //##ModelId=555C00FF037E
    virtual ~TerrestrialDeliverySystemDesc();

    //##ModelId=555C0019021D
    uint32_t centre_frequency;
    //##ModelId=555C00300054
    uint8_t FEC;
    //##ModelId=555C004200AF
    uint8_t modulation;
    //##ModelId=555C005A0135
    uint8_t number_of_subcarrier;
    //##ModelId=555C0076013D
    uint8_t frame_header_mode;
    //##ModelId=555C008D033C
    uint8_t interleaving_mode;
    //##ModelId=555C00B703D4
    bool other_frequency_flag;
    //##ModelId=555C00D40316
    bool sfn_mfn_flag;
};



#endif /* TERRESTRIALDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA3896C */
