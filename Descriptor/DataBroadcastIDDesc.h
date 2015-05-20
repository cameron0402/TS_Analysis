#ifndef DATABROADCASTIDDESC_H_HEADER_INCLUDED_AAA3A67D
#define DATABROADCASTIDDESC_H_HEADER_INCLUDED_AAA3A67D
#include "Descriptor.h"

// descriptor_tag = 0x66
//##ModelId=555C41440010
class DataBroadcastIDDesc : public Descriptor
{
  public:
    //##ModelId=555C416100DA
    DataBroadcastIDDesc();

    //##ModelId=555C416300C2
    DataBroadcastIDDesc(uint8_t* data);

    //##ModelId=555C4166014A
    virtual ~DataBroadcastIDDesc();

    //##ModelId=555C418B0191
    uint16_t data_broadcast_id;
    //##ModelId=555C41A20114
    uint8_t* id_selector;
};



#endif /* DATABROADCASTIDDESC_H_HEADER_INCLUDED_AAA3A67D */
