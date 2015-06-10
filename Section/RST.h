#ifndef RST_H_HEADER_INCLUDED_AA9BBED5
#define RST_H_HEADER_INCLUDED_AA9BBED5

#include "Section.h"

//##ModelId=556422D30241
class RST : public Section
{
  public:
    //##ModelId=5564233E03B6
    class RSInfo
    {
      public:
        //##ModelId=556423C803A8
        RSInfo();

        //##ModelId=556423D00236
        RSInfo(uint8_t* data);

        //##ModelId=556423D60087
        ~RSInfo();

        //##ModelId=55642347020E
        uint16_t transport_stream_id;
        //##ModelId=55642359003E
        uint16_t original_network_id;
        //##ModelId=5564236E002E
        uint16_t service_id;
        //##ModelId=556423850145
        uint16_t event_id;
        //##ModelId=5564239C0348
        uint8_t running_status;
    };

    //##ModelId=556422E4005E
    RST();

    //##ModelId=556422E703BD
    RST(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);

    //##ModelId=556422EB02DF
    virtual ~RST();

    //##ModelId=556424080386
    std::list<RSInfo*> rs_list;
};



#endif /* RST_H_HEADER_INCLUDED_AA9BBED5 */
