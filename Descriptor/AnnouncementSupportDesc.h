#ifndef ANNOUNCEMENTSUPPORTDESC_H_HEADER_INCLUDED_AAA38976
#define ANNOUNCEMENTSUPPORTDESC_H_HEADER_INCLUDED_AAA38976

#include "Descriptor.h"

//descriptor_tag = 0x6E
//##ModelId=555C4D7C020D
class AnnouncementSupportDesc : public Descriptor
{
  public:
    //##ModelId=555C4DB3037C
    class AnnounceInfo
    {
      public:
        //##ModelId=555C4DC9036E
        uint8_t announcement_type;
        //##ModelId=555C4DDD029D
        uint8_t reference_type;
        // when 0x01 <= reference_type <= 0x03 used
        //##ModelId=555C4DFB0067
        uint16_t original_network_id;
        //##ModelId=555C4E0B033C
        uint16_t transport_stream_id;
        //##ModelId=555C4E1803BC
        uint16_t service_id;
        //##ModelId=555C4E290036
        uint8_t component_tag;
    };

    //##ModelId=555C4D93028C
    AnnouncementSupportDesc();

    //##ModelId=555C4D9502A4
    AnnouncementSupportDesc(uint8_t* data);

    //##ModelId=555C4D97023C
    virtual ~AnnouncementSupportDesc();

    //##ModelId=555C4E720097
    uint16_t announcement_support_indicator;
    //##ModelId=555C4E7D013D
    std::list<AnnounceInfo> announce_list;
};



#endif /* ANNOUNCEMENTSUPPORTDESC_H_HEADER_INCLUDED_AAA38976 */
