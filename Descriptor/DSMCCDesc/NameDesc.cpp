#include "NameDesc.h"

NameDesc::NameDesc()
{

}

NameDesc::NameDesc(uint8_t* data)
    : Descriptor(data)
{
    name = new uint8_t[length + 1];
    name[length] = 0;
    memcpy(name, data + 2, length);
}

NameDesc::~NameDesc()
{
    if(name != NULL)
        delete []name;
}