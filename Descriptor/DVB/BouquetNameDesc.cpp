#include "BouquetNameDesc.h"

BouquetNameDesc::BouquetNameDesc(uint8_t* data) : Descriptor(data)
{
    bouquet_name = new uint8_t[length + 1];
    bouquet_name[length] = 0;
    memcpy(bouquet_name, data + 2, length);
}

//##ModelId=555A8CFB0209
BouquetNameDesc::~BouquetNameDesc()
{
    delete []bouquet_name;
}

