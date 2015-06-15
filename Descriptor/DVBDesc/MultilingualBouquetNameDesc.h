#ifndef MULTILINGUALBOUQUETNAMEDESC_H_HEADER_INCLUDED_AAA39401
#define MULTILINGUALBOUQUETNAMEDESC_H_HEADER_INCLUDED_AAA39401
#include "../Descriptor.h"

//descriptor_tag = 0x5C
//##ModelId=555C1F460396
class MultilingualBouquetNameDesc : public Descriptor
{
  public:
    //##ModelId=555C1F6E0154
    class BNameInfo
    {
      public:
        //##ModelId=555C1FD30014
        BNameInfo();

        //##ModelId=555C1FDA01B4
        BNameInfo(const BNameInfo& bnif);

        //##ModelId=555C1FE00151
        ~BNameInfo();

        //##ModelId=555C1F8803AC
        uint8_t ISO6392_language[3];
        //##ModelId=555C1F9E008C
        uint8_t bouquent_name_length;
        //##ModelId=555C1FB30163
        uint8_t* bouquent_name;
    };

    //##ModelId=555C203601EC
    MultilingualBouquetNameDesc();

    //##ModelId=555C20390113
    MultilingualBouquetNameDesc(uint8_t* data);

    //##ModelId=555C203E014C
    virtual ~MultilingualBouquetNameDesc();

    //##ModelId=555C20010232
    std::list<BNameInfo> bouname_list;
};



#endif /* MULTILINGUALBOUQUETNAMEDESC_H_HEADER_INCLUDED_AAA39401 */
