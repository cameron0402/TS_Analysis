#ifndef LINKAGEDESC_H_HEADER_INCLUDED_AAA54680
#define LINKAGEDESC_H_HEADER_INCLUDED_AAA54680
#include "../Descriptor.h"

// descriptor_tag = 0x4A
// warning : i don't deal with the private data. if needed please change the code 
//##ModelId=555A9FC202AA
class LinkageDesc : public Descriptor
{
  public:
    //##ModelId=555AA14C000F
    LinkageDesc();

    //##ModelId=555AA155006E
    LinkageDesc(uint8_t* data);

    //##ModelId=555AA16F024C
    virtual ~LinkageDesc();
    virtual void resolved();

    //##ModelId=555AA00A031C
    uint16_t transport_stream_id;
    //##ModelId=555AA02D027C
    uint16_t original_network_id;
    //##ModelId=555AA04D02A9
    uint16_t service_id;
    //##ModelId=555AA05F0364
    uint8_t linkage_type;
    // when linkage_type == 0x08
    //##ModelId=555AA07E0154
    uint8_t hand_over_type;
    //##ModelId=555AA0AC0115
    uint8_t origin_type;
    // while 0x01 <= hand_over_type <= 0x03
    //##ModelId=555AA0CA018F
    uint16_t network_id;
    // when origin_type == 0x00
    //##ModelId=555AA1200385
    uint16_t initial_service_id;
};



#endif /* LINKAGEDESC_H_HEADER_INCLUDED_AAA54680 */
