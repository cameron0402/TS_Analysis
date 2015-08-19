#ifndef LINKAGEDESC_H_HEADER_INCLUDED_AAA54680
#define LINKAGEDESC_H_HEADER_INCLUDED_AAA54680
#include "../Descriptor.h"

// descriptor_tag = 0x4A
// warning : i don't deal with the private data. if needed please change the code 
class LinkageDesc : public Descriptor
{
  public:
    LinkageDesc(uint8_t* data);
    virtual ~LinkageDesc();
    virtual void resolved();

    uint16_t transport_stream_id;
    uint16_t original_network_id;
    uint16_t service_id;
    uint8_t linkage_type;
    // when linkage_type == 0x08
    uint8_t hand_over_type;
    uint8_t origin_type;
    // while 0x01 <= hand_over_type <= 0x03
    uint16_t network_id;
    // when origin_type == 0x00
    uint16_t initial_service_id;
};



#endif /* LINKAGEDESC_H_HEADER_INCLUDED_AAA54680 */
