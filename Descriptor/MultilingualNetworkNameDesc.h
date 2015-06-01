#ifndef MULTILINGUALNETWORKNAMEDESC_H_HEADER_INCLUDED_AAA3C4E4
#define MULTILINGUALNETWORKNAMEDESC_H_HEADER_INCLUDED_AAA3C4E4
#include "Descriptor.h"

// descriptor_tag = 0x5B
//##ModelId=555C032F03B2
class MultilingualNetworkNameDesc : public Descriptor
{
  public:
    //##ModelId=555C03930089
    class MNameInfo
    {
      public:
        //##ModelId=555C1CB402A2
        MNameInfo();

        MNameInfo(uint8_t* data);

        //##ModelId=555C1CBC0072
        MNameInfo(const MNameInfo& mnif);

        //##ModelId=555C1CC201B6
        virtual ~MNameInfo();

        uint8_t ISO6392_language[3];
        //##ModelId=555C03C2012F
        uint8_t network_name_length;
        //##ModelId=555C03DE0165
        uint8_t* network_name;
    };

    //##ModelId=555C035401E5
    MultilingualNetworkNameDesc();

    //##ModelId=555C03570297
    MultilingualNetworkNameDesc(uint8_t* data);

    //##ModelId=555C036901A6
    virtual ~MultilingualNetworkNameDesc();
    virtual void resolved();

    //##ModelId=555C03FC0191
    std::list<MNameInfo*> netname_list;
};



#endif /* MULTILINGUALNETWORKNAMEDESC_H_HEADER_INCLUDED_AAA3C4E4 */
