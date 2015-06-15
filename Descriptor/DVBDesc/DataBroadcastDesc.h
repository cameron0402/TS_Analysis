#ifndef DATABROADCASTDESC_H_HEADER_INCLUDED_AAA3AD3E
#define DATABROADCASTDESC_H_HEADER_INCLUDED_AAA3AD3E
#include "../Descriptor.h"

//descriptor_tag = 0x64
//##ModelId=555C3C940224
class DataBroadcastDesc : public Descriptor
{
  public:
    //##ModelId=555C3D4F013A
    DataBroadcastDesc();

    //##ModelId=555C3D510249
    DataBroadcastDesc(uint8_t* data);

    //##ModelId=555C3D5302AA
    virtual ~DataBroadcastDesc();

    //##ModelId=555C3CB20281
    uint16_t data_broadcast_id;
    //##ModelId=555C3CC50339
    uint8_t component_tag;
    //##ModelId=555C3CDC01E1
    uint8_t selector_length;
    //##ModelId=555C3CE803E3
    uint8_t* selector;
    //##ModelId=555C3D0501E5
    uint8_t ISO6392_language[3];
    //##ModelId=555C3D23004C
    uint8_t text_length;
    //##ModelId=555C3D370349
    uint8_t* text;
};



#endif /* DATABROADCASTDESC_H_HEADER_INCLUDED_AAA3AD3E */
