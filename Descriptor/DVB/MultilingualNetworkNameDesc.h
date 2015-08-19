#ifndef MULTILINGUALNETWORKNAMEDESC_H_HEADER_INCLUDED_AAA3C4E4
#define MULTILINGUALNETWORKNAMEDESC_H_HEADER_INCLUDED_AAA3C4E4
#include "../Descriptor.h"

// descriptor_tag = 0x5B
class MultilingualNetworkNameDesc : public Descriptor
{
  public:

    class MNameInfo
    {
      public:
        MNameInfo(uint8_t* data);
        MNameInfo(const MNameInfo& mnif);
        virtual ~MNameInfo();

        uint8_t ISO6392_language[4];
        uint8_t network_name_length;
        uint8_t* network_name;
    };

    MultilingualNetworkNameDesc(uint8_t* data);
    virtual ~MultilingualNetworkNameDesc();
    virtual void resolved();


    std::list<MNameInfo*> netname_list;
};



#endif /* MULTILINGUALNETWORKNAMEDESC_H_HEADER_INCLUDED_AAA3C4E4 */
