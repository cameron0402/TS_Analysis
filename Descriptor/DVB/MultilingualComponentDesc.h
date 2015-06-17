#ifndef MULTILINGUALCOMPONENTDESC_H_HEADER_INCLUDED_AAA3F54C
#define MULTILINGUALCOMPONENTDESC_H_HEADER_INCLUDED_AAA3F54C
#include "../Descriptor.h"

//descriptor_tag = 0x5E
//##ModelId=555C27AF0280
class MultilingualComponentDesc : public Descriptor
{
  public:
    //##ModelId=555C27E00344
    class ComponentInfo
    {
      public:
        //##ModelId=555C2851011E
        ComponentInfo();

        //##ModelId=555C285E0376
        ComponentInfo(const ComponentInfo& cpif);

        //##ModelId=555C287E0244
        ~ComponentInfo();

        //##ModelId=555C280A01A5
        uint8_t ISO6392_language[3];
        //##ModelId=555C282002CF
        uint8_t text_description_length;
        //##ModelId=555C283D003D
        uint8_t* text_description;
    };

    //##ModelId=555C27C7029B
    MultilingualComponentDesc();

    //##ModelId=555C27C902B3
    MultilingualComponentDesc(uint8_t* data);

    //##ModelId=555C27CB0284
    virtual ~MultilingualComponentDesc();

    //##ModelId=555C288901B4
    uint8_t component_tag;
    //##ModelId=555C289A029C
    std::list<ComponentInfo> component_list;
};



#endif /* MULTILINGUALCOMPONENTDESC_H_HEADER_INCLUDED_AAA3F54C */
