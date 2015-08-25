#include "ComponentDesc.h"

ComponentDesc::ComponentDesc(uint8_t* data)
    : Descriptor(data),
      stream_content(data[2] & 0x0F),
      component_type(data[3]),
      component_tag(data[4]),
      ISO6392_language(),
      text(NULL)
{
    memcpy(ISO6392_language, data + 5, 3);
    text = new uint8_t[length - 5];
    text[length - 6] = 0;
    memcpy(text, data + 8, length - 6);
}

ComponentDesc::~ComponentDesc()
{
    delete []text;
}

