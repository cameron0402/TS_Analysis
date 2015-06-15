#include "MultilingualComponentDesc.h"

//##ModelId=555C2851011E
MultilingualComponentDesc::ComponentInfo::ComponentInfo()
{
}

//##ModelId=555C285E0376
MultilingualComponentDesc::ComponentInfo::ComponentInfo(const ComponentInfo& cpif)
{
    if(&cpif == this)
        return ;
    memcpy(ISO6392_language, cpif.ISO6392_language, 3);
    text_description_length = cpif.text_description_length;
    text_description = new uint8_t[text_description_length];
    memcpy(text_description, cpif.text_description, text_description_length);
}

//##ModelId=555C287E0244
MultilingualComponentDesc::ComponentInfo::~ComponentInfo()
{
    delete []text_description;
}

//##ModelId=555C27C7029B
MultilingualComponentDesc::MultilingualComponentDesc()
{
}

//##ModelId=555C27C902B3
MultilingualComponentDesc::MultilingualComponentDesc(uint8_t* data)
    : Descriptor(data),
      component_tag(data[2])
{
    int index = 3; 
    while(index < length + 2)
    { 
        ComponentInfo tmp;
        memcpy(tmp.ISO6392_language, data + index, 3);
        tmp.text_description_length = data[index + 4];
        tmp.text_description = new uint8_t[tmp.text_description_length];
        memcpy(tmp.text_description, data + 5 + index, tmp.text_description_length);
        index += 5 + tmp.text_description_length;
        component_list.push_back(tmp);
    }
}

//##ModelId=555C27CB0284
MultilingualComponentDesc::~MultilingualComponentDesc()
{
}

