#include "InfoDesc.h"

InfoDesc::InfoDesc()
{

}

InfoDesc::InfoDesc(uint8_t* data)
    : Descriptor(data)
{
    memcpy(ISO_639_language, data + 2, 3);
    info = new uint8_t[length - 2];
    info[length - 3] = 0;
    memcpy(info, data + 5, length - 3);
}

InfoDesc::~InfoDesc()
{
    if(info != NULL)
        delete []info;
}