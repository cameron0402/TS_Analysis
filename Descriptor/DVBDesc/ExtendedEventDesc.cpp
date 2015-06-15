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
    uint8_t* pd = data + 7;
    ItemInfo* ii;
    while(index < length_of_items)
    {
        ii = new ItemInfo(pd + index);
        item_list.push_back(ii);
        index += 2 + ii->item_description_length + ii->item_length;
    }

    text_length = data[7 + index];
    text = new uint8_t[text_length + 1];
    text[text_length] = 0;
    memcpy(text, data + 8 + index, text_length);
}

//##ModelId=555AB27001B9
ExtendedEventDesc::~ExtendedEventDesc()
{
    std::list<ItemInfo*>::iterator iit;
    for(iit = item_list.begin(); iit != item_list.end(); ++iit)
    {
        delete (*iit);
    }
    item_list.clear();
    delete []text;
}


ExtendedEventDesc::ItemInfo::ItemInfo(uint8_t* data)
    : item_description_length(data[0]),
      item_length(data[1 + item_description_length])
{
    item_description = new uint8_t[item_description_length + 1];
    item_description[item_description_length] = 0;
    memcpy(item_description, data + 1, item_description_length);

    item = new uint8_t[item_length + 1];
    item[item_length] = 0;
    memcpy(item, data + 2 + item_description_length, item_length);
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

void ExtendedEventDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("extended_event_descriptor");

    sprintf(arr, "0x%x", descriptor_number);
    tmp = new TiXmlElement("descriptor_number");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", last_descriptor_number);
    tmp = new TiXmlElement("last_descriptor_number");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    memcpy(arr, ISO6392_language, 3);
    arr[3] = 0;
    tmp = new TiXmlElement("ISO_639_2_language_code");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", length_of_items);
    tmp = new TiXmlElement("length_of_items");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    if(!item_list.empty())
    {
        std::list<ItemInfo*>::iterator iit;
        for(iit = item_list.begin(); iit != item_list.end(); ++iit)
        {
            tmp = new TiXmlElement("Item");
            TiXmlElement* tms;

            sprintf(arr, "0x%x", (*iit)->item_description_length);
            tms = new TiXmlElement("item_description_length");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            tms = new TiXmlElement("item_description");
            tms->LinkEndChild(new TiXmlElement((const char*)(*iit)->item_description));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*iit)->item_length);
            tms = new TiXmlElement("item_length");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            tms = new TiXmlElement("item");
            tms->LinkEndChild(new TiXmlElement((const char*)(*iit)->item));
            tmp->LinkEndChild(tms);

            xml->LinkEndChild(tmp);
        }
    }

    sprintf(arr, "0x%x", text_length);
    tmp = new TiXmlElement("text_length");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);


    tmp = new TiXmlElement("text");
    tmp->LinkEndChild(new TiXmlText((const char*)text));
    xml->LinkEndChild(tmp);
}

