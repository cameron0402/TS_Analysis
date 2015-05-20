#include "MultilingualBouquetNameDesc.h"

//##ModelId=555C1FD30014
MultilingualBouquetNameDesc::BNameInfo::BNameInfo()
{
}

//##ModelId=555C1FDA01B4
MultilingualBouquetNameDesc::BNameInfo::BNameInfo(const BNameInfo& bnif)
{
    if(&bnif == this)
        return ;
    memcpy(ISO6392_language, bnif.ISO6392_language, 3);
    bouquent_name_length = bnif.bouquent_name_length;
    bouquent_name = new uint8_t[bouquent_name_length];
    memcpy(bouquent_name, bnif.bouquent_name, bouquent_name_length);
}

//##ModelId=555C1FE00151
MultilingualBouquetNameDesc::BNameInfo::~BNameInfo()
{
    delete []bouquent_name;
}

//##ModelId=555C203601EC
MultilingualBouquetNameDesc::MultilingualBouquetNameDesc()
{
}

//##ModelId=555C20390113
MultilingualBouquetNameDesc::MultilingualBouquetNameDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2; 
    while(index < length + 2)
    {
        BNameInfo tmp;
        memcpy(tmp.ISO6392_language, data + index, 3);
        tmp.bouquent_name_length = data[index + 4];
        tmp.bouquent_name = new uint8_t[tmp.bouquent_name_length];
        memcpy(tmp.bouquent_name, data + 5 + index, tmp.bouquent_name_length);
        index += 5 + tmp.bouquent_name_length;
        bouname_list.push_back(tmp);
    }
}

//##ModelId=555C203E014C
MultilingualBouquetNameDesc::~MultilingualBouquetNameDesc()
{
}

