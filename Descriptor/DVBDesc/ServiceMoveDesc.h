#ifndef SERVICEMOVEDESC_H_HEADER_INCLUDED_AAA3AB99
#define SERVICEMOVEDESC_H_HEADER_INCLUDED_AAA3AB99
#include "../Descriptor.h"

//descriptor_tag = 0x60
//##ModelId=555C2E22005A
class ServiceMoveDesc : public Descriptor
{
  public:
    //##ModelId=555C2E320366
    ServiceMoveDesc();

    //##ModelId=555C2E38018D
    ServiceMoveDesc(uint8_t* data);

    //##ModelId=555C2E3B0026
    virtual ~ServiceMoveDesc();

    //##ModelId=555C2E6602B7
    uint16_t new_original_network_id;
    //##ModelId=555C2E80001E
    uint16_t new_transport_stream_id;
    //##ModelId=555C2EA20318
    uint16_t new_service_id;
};



#endif /* SERVICEMOVEDESC_H_HEADER_INCLUDED_AAA3AB99 */
