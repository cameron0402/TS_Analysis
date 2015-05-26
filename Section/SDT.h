#ifndef SDT_H_HEADER_INCLUDED_AA9C3B80
#define SDT_H_HEADER_INCLUDED_AA9C3B80

#include "Section.h"

class Descriptor;

//##ModelId=5563CBA7031B
class SDT : public Section
{
  public:
    //##ModelId=5563CCAB0157
    class ServiceInfo
    {
      public:
        //##ModelId=5563D0B20194
        ServiceInfo();

        //##ModelId=5563D0B900DD
        ServiceInfo(uint8_t* data);

        //##ModelId=5563D0D1019A
        virtual ~ServiceInfo();

        uint16_t service_id;
        //##ModelId=5563CCCA035F
        bool EIT_schedule_flag;
        //##ModelId=5563CCE40233
        bool EIT_present_following_flag;
        //##ModelId=5563CD000370
        uint8_t running_status;
        //##ModelId=5563CD2E018E
        bool free_CA_mode;
        //##ModelId=5563CD460274
        uint16_t descriptors_loop_length;
        //##ModelId=5563CD5E01DA
        std::list<Descriptor*> desc_list;
    };

    //##ModelId=5563CDBD00BF
    SDT();

    //##ModelId=5563CDCB02BF
    SDT(uint8_t* data, uint16_t len);

    //##ModelId=5563CE0800BB
    virtual ~SDT();

    virtual bool joinTo(SectionFactory* sf);
    bool operator ==(const SDT& st);

    //##ModelId=5563CBB70111
    uint16_t transport_stream_id;
    //##ModelId=5563CBCC01CD
    uint8_t version_number;
    //##ModelId=5563CBDF00F9
    bool current_next_indicator;
    //##ModelId=5563CBF3032D
    uint8_t section_number;
    //##ModelId=5563CC060258
    uint8_t last_section_number;
    //##ModelId=5563CC3D0105
    uint16_t original_network_id;
    //##ModelId=5563CD7A0250
    std::list<ServiceInfo*> service_list;
    //##ModelId=5563CD9902C2
    uint32_t crc32;
};



#endif /* SDT_H_HEADER_INCLUDED_AA9C3B80 */
