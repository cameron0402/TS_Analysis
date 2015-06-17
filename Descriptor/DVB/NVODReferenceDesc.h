#ifndef NVODREFERENCEDESC_H_HEADER_INCLUDED_AAA56850
#define NVODREFERENCEDESC_H_HEADER_INCLUDED_AAA56850
#include "../Descriptor.h"

//descriptor_tag = 0x4B
//##ModelId=555AA4B00162
class NVODReferenceDesc : public Descriptor
{
  public:
    //##ModelId=555AA51F03C5
    class NVODReferInfo
    {
      public:
        //##ModelId=555AA5300227
        uint16_t transport_stream_id;
        //##ModelId=555AA549002F
        uint16_t original_network_id;
        //##ModelId=555AA55D0046
        uint16_t service_id;
    };

    //##ModelId=555AA5AF003F
    NVODReferenceDesc();

    //##ModelId=555AA5BA02C5
    NVODReferenceDesc(uint8_t* data);

    //##ModelId=555AA5D2027F
    virtual ~NVODReferenceDesc();

    //##ModelId=555AA57800CE
    std::list<NVODReferInfo> refer_list;
};



#endif /* NVODREFERENCEDESC_H_HEADER_INCLUDED_AAA56850 */
