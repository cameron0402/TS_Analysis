#include "DataBroadcastDesc.h"

//##ModelId=555C3D4F013A
DataBroadcastDesc::DataBroadcastDesc()
{
}

//##ModelId=555C3D510249
DataBroadcastDesc::DataBroadcastDesc(uint8_t* data)
    : Descriptor(data), 
      data_broadcast_id((data[2] << 8) | data[3]),
      component_tag(data[4]),
      selector_length(data[5]),
      text_length(data[9 + selector_length])
{
    selector = new uint8_t[selector_length];
    memcpy(selector, data + 6, selector_length);

    memcpy(ISO6392_language, data + 6 + selector_length, 3);
    text = new uint8_t[text_length];
    memcpy(text, data + 10 + selector_length, text_length);
}

//##ModelId=555C3D5302AA
DataBroadcastDesc::~DataBroadcastDesc()
{
    delete []selector;
    delete []text;
}

