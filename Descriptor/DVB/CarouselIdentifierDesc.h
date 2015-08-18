#ifndef _CAROUSEL_IDENTIFIER_DESC_
#define _CAROUSEL_IDENTIFIER_DESC_

#include "../Descriptor.h"

//descriptor_tag = 0x13
class CarouselIdentifierDesc : public Descriptor
{
public:
    class FormatSpecifier
    {
    public:
        FormatSpecifier(uint8_t* data);
        ~FormatSpecifier();

        uint8_t module_version;
        uint16_t module_id;
        uint16_t block_size;
        uint32_t module_size;
        uint8_t compression_method;
        uint32_t original_size;
        uint8_t time_out; // s
        uint8_t objkey_length;
        uint32_t objkey;
    };

    CarouselIdentifierDesc(uint8_t* data);
    virtual ~CarouselIdentifierDesc();

    uint32_t carousel_id;
    uint8_t format_id;
    FormatSpecifier* format_speci;
    //uint8_t* prv_data;
};

#endif