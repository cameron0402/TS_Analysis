#include "Descriptor.h"

Descriptor::Descriptor()
{

}

Descriptor::Descriptor(uint8_t* data) 
    : tag(data[0]), 
      length(data[1])
{
}


Descriptor::~Descriptor()
{

}

//##ModelId=5555699A0028
void Descriptor::resolved()
{
}

