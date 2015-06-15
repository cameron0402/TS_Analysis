#include "TypeDesc.h"

TypeDesc::TypeDesc()
{

}

TypeDesc::TypeDesc(uint8_t* data)
    : Descriptor(data)
{
    type = new uint8_t[length + 1];
    type[length] = 0;
    memcpy(type, data + 2, length);
}

TypeDesc::~TypeDesc()
{
    if(type != NULL)
        delete []type;
};