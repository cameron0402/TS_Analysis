#ifndef NIT_H_HEADER_INCLUDED_AAAA2DF4
#define NIT_H_HEADER_INCLUDED_AAAA2DF4
#include "Section.h"
class Descriptor;

//##ModelId=555584E1029F
class NIT : public Section
{
  public:
    //##ModelId=5555865F036F
    class TransStreamInfo
    {
      public:
        //##ModelId=555D8D48003E
        TransStreamInfo();

        //##ModelId=55558677030F
        //##ModelId=555D8D580325
        TransStreamInfo(uint8_t* data);

        
        //##ModelId=555D8D5B00B0
        virtual ~TransStreamInfo();

        uint16_t transport_stream_id;
        //##ModelId=55558698006F
        uint16_t original_network_id;
        //##ModelId=555586CD00F7
        uint16_t transport_descriptors_length;
        //##ModelId=555587030350
        std::list<Descriptor*> desc_list;
    };

    //##ModelId=5555875B00F0
    NIT();

    //##ModelId=55558761023E
    NIT(uint8_t* data, uint16_t len);
    //##ModelId=555828A60271
    virtual ~NIT();


    //##ModelId=555584FE01EE
    uint16_t network_descriptors_length;
    //##ModelId=5555858902AE
    std::list<Descriptor*> desc_list;
    //##ModelId=555586230017
    uint16_t transport_stream_loop_length;
    //##ModelId=555D8D18028A
    std::list<TransStreamInfo*> streaminfo_list;
};



#endif /* NIT_H_HEADER_INCLUDED_AAAA2DF4 */
