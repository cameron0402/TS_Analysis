#ifndef SIT_H_HEADER_INCLUDED_AA9AB17A
#define SIT_H_HEADER_INCLUDED_AA9AB17A

#include "../Section.h"

class Descriptor;

//##ModelId=556428C30380
class SIT : public Section
{
  public:
    //##ModelId=556429B503B0
    class ServiceInfo
    {
      public:
        //##ModelId=556429E100BC
        ServiceInfo();

        //##ModelId=556429E800A8
        ServiceInfo(uint8_t* data);

        //##ModelId=556429EE0080
        virtual ~ServiceInfo();

        //##ModelId=55642A1C01E9
        uint16_t service_id;
        //##ModelId=55642A2C0020
        uint8_t running_status;
        //##ModelId=55642A400220
        uint16_t service_loop_length;
        //##ModelId=55642A520350
        std::list<Descriptor*> desc_list;
    };

    //##ModelId=556428CC02B1
    SIT();

    //##ModelId=556428CF03E6
    SIT(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);

    //##ModelId=556428D30298
    virtual ~SIT();

    //##ModelId=5564290F0238
    uint8_t version_number;
    //##ModelId=5564291E02A7
    bool current_next_indicator;
    //##ModelId=5564293500A1
    uint8_t section_number;
    //##ModelId=556429450155
    uint8_t last_section_number;
    //##ModelId=5564295B00C7
    uint16_t transmission_info_loop_length;
    //##ModelId=5564298E0080
    std::list<Descriptor*> desc_list;
    //##ModelId=55642A9601A0
    std::list<ServiceInfo*> service_list;
    //##ModelId=55642AAA02F9
    uint32_t crc32;
};



#endif /* SIT_H_HEADER_INCLUDED_AA9AB17A */
