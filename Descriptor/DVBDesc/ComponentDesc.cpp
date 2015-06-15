#include "ComponentDesc.h"

//##ModelId=555ADBDF0056
ComponentDesc::ComponentDesc()
{
}

//##ModelId=555ADBE900B2
ComponentDesc::ComponentDesc(uint8_t* data)
    : Descriptor(data),
      stream_content(data[2] & 0x0F),
      component_type(data[3]),
      component_tag(data[4])
{
    memcpy(ISO6392_language, data + 5, 3);
    text = new uint8_t[length - 6];
    memcpy(text, data + 8, length - 6);
}

//##ModelId=555ADBFF02F1
ComponentDesc::~ComponentDesc()
{
    delete []text;
}

