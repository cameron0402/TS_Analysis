#include "TOT.h"
#include "SectionFactory.h"
#include "../Descriptor/Descriptor.h"
#include "../Descriptor/DescFactory.h"

//##ModelId=55640EA801B6
TOT::TOT()
{
}

//##ModelId=55640EAC00FC
TOT::TOT(uint8_t* data, uint16_t len)
    : Section(data, len),
      UTC_time((data[3] << 32) | (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]),
      descriptors_loop_length(((data[8] & 0xF) << 8) | data[9]),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    int index = 10;
    DescFactory des_fac;
    while(index < len - 4)
    {
        Descriptor* des = des_fac.createDesc(data[index], data + index);
        desc_list.push_back(des);
        index += des->length + 2;
    }
}

//##ModelId=55640EAF034C
TOT::~TOT()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

bool TOT::joinTo(SectionFactory* sf)
{
    if(sf->tot != NULL)
        return false;
    
    sf->tot = this;
    return true;
}

