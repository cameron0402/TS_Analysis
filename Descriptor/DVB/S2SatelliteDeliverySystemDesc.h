#ifndef S2SATELLITEDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA29892
#define S2SATELLITEDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA29892
#include "../Descriptor.h"

// descriptor_tag = 0x79
//##ModelId=555D3F9102B9
class S2SatelliteDeliverySystemDesc : public Descriptor
{
  public:
    //##ModelId=555D3FAD0008
    S2SatelliteDeliverySystemDesc();

    //##ModelId=555D3FB30261
    S2SatelliteDeliverySystemDesc(uint8_t* data);

    //##ModelId=555D3FB5024E
    virtual ~S2SatelliteDeliverySystemDesc();

    //##ModelId=555D40070102
    bool scrambling_sequence_selector;
    //##ModelId=555D402803C1
    bool multiple_input_stream_flag;
    //##ModelId=555D4059021C
    bool backwards_compatibility_indicator;
    //##ModelId=555D406D024D
    uint32_t scrambling_sequence_index;
    //##ModelId=555D40800398
    uint8_t input_stream_identifier;
};



#endif /* S2SATELLITEDELIVERYSYSTEMDESC_H_HEADER_INCLUDED_AAA29892 */
