#include "BouquetNameDesc.h"

//##ModelId=555A8CC90092
BouquetNameDesc::BouquetNameDesc()
{
}

//##ModelId=555A8CE10380
BouquetNameDesc::BouquetNameDesc(uint8_t* data) : Descriptor(data)
{
    bouquet_name = new uint8_t[length];
    memcpy(bouquet_name, data + 2, length);
}

//##ModelId=555A8CFB0209
BouquetNameDesc::~BouquetNameDesc()
{
    delete []bouquet_name;
}

