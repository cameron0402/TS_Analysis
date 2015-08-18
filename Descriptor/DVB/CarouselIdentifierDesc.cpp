#include "CarouselIdentifierDesc.h"

CarouselIdentifierDesc::FormatSpecifier::FormatSpecifier(uint8_t* data)
    : module_version(data[0]),
    module_id((data[1] << 8) | data[2]),
    block_size((data[3] << 8) | data[4]),
    module_size((data[5] << 24) | (data[6] << 16) | (data[7] << 8) | data[8]),
    compression_method(data[9]),
    original_size((data[10] << 24) | (data[11] << 16) | (data[12] << 8) | data[13]),
    objkey_length(data[14]),
    objkey(0)
{
    for(int i = 0; i < objkey_length; ++i)
    {
        objkey << 8;
        objkey |= data[15 + i];
    }
}

CarouselIdentifierDesc::FormatSpecifier::~FormatSpecifier()
{

}

CarouselIdentifierDesc::CarouselIdentifierDesc(uint8_t* data)
    : Descriptor(data),
    carousel_id((data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5]),
    format_id(data[6]),
    format_speci(NULL)
{
    if(format_id == 0x1)
    {
        format_speci = new FormatSpecifier(data + 7);
    }
}

CarouselIdentifierDesc::~CarouselIdentifierDesc()
{
    if(format_speci != NULL)
        delete format_speci;
}
