#ifndef RST_H_HEADER_INCLUDED_AA9BBED5
#define RST_H_HEADER_INCLUDED_AA9BBED5

#include "../Section.h"

//##ModelId=556422D30241
class RST : public Section
{
  public:
    class RSInfo
    {
      public:
        RSInfo(uint8_t* data);
        ~RSInfo();

        uint16_t transport_stream_id;
        uint16_t original_network_id;
        uint16_t service_id;
        uint16_t event_id;
        uint8_t running_status;
    };

    RST(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~RST();

    std::list<RSInfo*> rs_list;
};



#endif /* RST_H_HEADER_INCLUDED_AA9BBED5 */
