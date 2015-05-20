#include "ExtendedEventDesc.h"

//##ModelId=555AB244012B
ExtendedEventDesc::ExtendedEventDesc()
{
}

//##ModelId=555AB25102B3
ExtendedEventDesc::ExtendedEventDesc(uint8_t* data) 
    : Descriptor(data),
      descriptor_number(data[2] >> 4),
      last_descriptor_number(data[2] & 0x1f),
      length_of_items(data[6])
{
    memcpy(ISO6392_language, data + 3, 3);
    int index = 0;
    while(index < length_of_items)
    {
        ItemInfo tmp;
        tmp.item_description_length = data[7 + index];
        tmp.item_description = new uint8_t[tmp.item_description_length];
        memcpy(tmp.item_description, data + 8 + index, tmp.item_description_length);

        tmp.item_length = data[8 + index + tmp.item_description_length];
        tmp.item = new uint8_t[tmp.item_length];
        memcpy(tmp.item, data + 9 + index + tmp.item_description_length, tmp.item_length);

        item_list.push_back(tmp);

        index += 2 + tmp.item_description_length + tmp.item_length;
    }

    text_length = data[7 + index];
    text = new uint8_t[text_length];
    memcpy(text, data + 8 + index, text_length);
}

//##ModelId=555AB27001B9
ExtendedEventDesc::~ExtendedEventDesc()
{
   delete []text;
}

//##ModelId=555AB2FD0182
ExtendedEventDesc::ItemInfo::ItemInfo(const ItemInfo& itf)
{
    if(&itf == this)
        return;
    item_description_length = itf.item_description_length;
    item_description = new uint8_t[item_description_length];
    memcpy(item_description, itf.item_description, item_description_length);
    item_length = itf.item_length;
    item = new uint8_t[item_length];
    memcpy(item, itf.item, item_length);
}

//##ModelId=555AB33A00B3
ExtendedEventDesc::ItemInfo::~ItemInfo()
{
    delete []item_description;
    delete []item;
}

//##ModelId=555AB34B0012
ExtendedEventDesc::ItemInfo::ItemInfo()
{
}

