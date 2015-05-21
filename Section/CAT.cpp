#include "CAT.h"
#include "../Descriptor/Descriptor.h"
#include "../Descriptor/DescFactory.h"

//##ModelId=55558B3703CA
CAT::CAT()
{
}

//##ModelId=55558B3E03C8
CAT::CAT(uint8_t* data, uint16_t len) : Section(data, len)
{
    int index = 8;
    DescFactory des_fac;
    while(index < len - 4)
    {
        Descriptor* des = des_fac.createDesc(data[index], data + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }
}

CAT::~CAT()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

