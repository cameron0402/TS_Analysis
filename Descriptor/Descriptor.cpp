#include "Descriptor.h"

Descriptor::Descriptor() : xml(NULL)
{

}

Descriptor::Descriptor(uint8_t* data) 
    : tag(data[0]), 
      length(data[1]),
      xml(NULL)
{
}


Descriptor::~Descriptor()
{

}

//##ModelId=5555699A0028
void Descriptor::resolved()
{
}

