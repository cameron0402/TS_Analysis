#ifndef EXTENDEDEVENTDESC_H_HEADER_INCLUDED_AAA54031
#define EXTENDEDEVENTDESC_H_HEADER_INCLUDED_AAA54031
#include "../Descriptor.h"

//descriptor_tag = 0x4E
//##ModelId=555AB07C0226
class ExtendedEventDesc : public Descriptor
{
  public:
    //##ModelId=555AB1280073
    class ItemInfo
    {
      public:
        ItemInfo(const ItemInfo& itf);
        ItemInfo(uint8_t* data);
        virtual ~ItemInfo();

        uint8_t item_description_length;
        uint8_t* item_description;
        uint8_t item_length;
        uint8_t* item;
    };

    ExtendedEventDesc(uint8_t* data);
    virtual ~ExtendedEventDesc();

    virtual void resolved();
    uint8_t descriptor_number;
    uint8_t last_descriptor_number;
    uint8_t ISO6392_language[4];
    uint8_t length_of_items;
    std::list<ItemInfo*> item_list;
    uint8_t text_length;
    uint8_t* text;
};



#endif /* EXTENDEDEVENTDESC_H_HEADER_INCLUDED_AAA54031 */
