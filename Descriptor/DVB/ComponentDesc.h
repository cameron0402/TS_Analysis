#ifndef COMPONENTDESC_H_HEADER_INCLUDED_AAA5317F
#define COMPONENTDESC_H_HEADER_INCLUDED_AAA5317F
#include "../Descriptor.h"

//descriptor_tag = 0x50
class ComponentDesc : public Descriptor
{
  public:
    ComponentDesc(uint8_t* data);
    virtual ~ComponentDesc();

    uint8_t stream_content;
    uint8_t component_type;
    uint8_t component_tag;
    uint8_t ISO6392_language[4];
    uint8_t* text;
};



#endif /* COMPONENTDESC_H_HEADER_INCLUDED_AAA5317F */
