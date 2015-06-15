#ifndef HIERARCHYDESC_H_HEADER_INCLUDED_AAA796C7
#define HIERARCHYDESC_H_HEADER_INCLUDED_AAA796C7
#include "../Descriptor.h"

//descriptor_tag = 0x04

//##ModelId=55582ECE00F5
class HierarchyDesc : public Descriptor
{
  public:
    //##ModelId=55582F990002
    HierarchyDesc();

    //##ModelId=55582FA4037A
    HierarchyDesc(uint8_t* data);

    //##ModelId=55582FCE01C3
    virtual ~HierarchyDesc();

    //##ModelId=55582EFC0121
    uint8_t hierarchy_type;
    //##ModelId=55582F210101
    uint8_t hierarchy_layer_index;
    //##ModelId=55582F470173
    uint8_t hierarchy_embedded_layer;
    //##ModelId=55582F760030
    uint8_t hierarchy_priority;
};



#endif /* HIERARCHYDESC_H_HEADER_INCLUDED_AAA796C7 */
