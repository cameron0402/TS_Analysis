#ifndef EXTENDEDEVENTDESC_H_HEADER_INCLUDED_AAA54031
#define EXTENDEDEVENTDESC_H_HEADER_INCLUDED_AAA54031
#include "Descriptor.h"

//descriptor_tag = 0x4E
//##ModelId=555AB07C0226
class ExtendedEventDesc : public Descriptor
{
  public:
    //##ModelId=555AB1280073
    class ItemInfo
    {
      public:
        //##ModelId=555AB2FD0182
        ItemInfo(const ItemInfo& itf);

        //##ModelId=555AB13300AB
        //##ModelId=555AB33A00B3
        virtual ~ItemInfo();

        
        //##ModelId=555AB34B0012
        ItemInfo();

        uint8_t item_description_length;
        //##ModelId=555AB14E0063
        uint8_t* item_description;
        //##ModelId=555AB163021F
        uint8_t item_length;
        //##ModelId=555AB17C03D0
        uint8_t* item;
    };

    //##ModelId=555AB244012B
    ExtendedEventDesc();

    //##ModelId=555AB25102B3
    ExtendedEventDesc(uint8_t* data);

    //##ModelId=555AB27001B9
    virtual ~ExtendedEventDesc();

    //##ModelId=555AB0AA0362
    uint8_t descriptor_number;
    //##ModelId=555AB0C602FA
    uint8_t last_descriptor_number;
    //##ModelId=555AB0E80192
    uint8_t ISO6392_language[3];
    //##ModelId=555AB1090332
    uint8_t length_of_items;
    //##ModelId=555AB1DF0282
    std::list<ItemInfo> item_list;
    //##ModelId=555AB20C017A
    uint8_t text_length;
    //##ModelId=555AB21D0164
    uint8_t* text;
};



#endif /* EXTENDEDEVENTDESC_H_HEADER_INCLUDED_AAA54031 */
