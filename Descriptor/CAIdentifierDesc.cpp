#include "CAIdentifierDesc.h"

//##ModelId=555AF5260307
CAIdentifierDesc::CAIdentifierDesc()
{
}

//##ModelId=555AF5300236
CAIdentifierDesc::CAIdentifierDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    while(index < length + 1)
    {
        CA_id_list.push_back((data[index] << 8) | data[index + 1]);
        index += 2;
    }
}

//##ModelId=555AF54802F5
CAIdentifierDesc::~CAIdentifierDesc()
{
}

