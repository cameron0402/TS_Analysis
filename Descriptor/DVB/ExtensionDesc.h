#ifndef EXTENSIONDESC_H_HEADER_INCLUDED_AAA28DD1
#define EXTENSIONDESC_H_HEADER_INCLUDED_AAA28DD1
#include "../Descriptor.h"

//##ModelId=555D4ACA00F4
class ExtensionDesc : public Descriptor
{
  public:
    //##ModelId=555D4AE901DF
    ExtensionDesc();

    //##ModelId=555D4AEB015F
    ExtensionDesc(uint8_t* data);

    //##ModelId=555D4AED0017
    virtual ~ExtensionDesc();

    //##ModelId=555D4B0C0131
    uint8_t descriptor_tag_extension;
    //##ModelId=555D4B250001
    uint8_t* selector;
};



#endif /* EXTENSIONDESC_H_HEADER_INCLUDED_AAA28DD1 */
