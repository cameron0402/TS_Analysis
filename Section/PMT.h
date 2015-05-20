#ifndef PMT_H_HEADER_INCLUDED_AAAA79D3
#define PMT_H_HEADER_INCLUDED_AAAA79D3
#include "Section.h"
#include <list>
class Descriptor;

//##ModelId=555569F70169
class PMT : public Section
{
  public:
    //##ModelId=55558221017D
    class StreamInfo
    {
      public:
        // stream_type
        //##ModelId=55558250017E
        uint8_t type;
        // elementary_PID
        //##ModelId=5555826F0328
        uint16_t elem_PID;
        // ES_info_length
        //##ModelId=5555829203E6
        uint16_t info_length;
        //##ModelId=555582AE03CD
        std::list<Descriptor*> desc_list;
    };

    //##ModelId=55556B720001
    PMT();

    //##ModelId=55556B820369
    PMT(void* data, uint16_t len);

    virtual ~PMT();

    //##ModelId=55556A4E0217
    uint16_t PCR_PID;
    //##ModelId=55556A820381
    uint16_t program_info_length;
    //##ModelId=55556ACF0381
    std::list<StreamInfo> stream_list;
};



#endif /* PMT_H_HEADER_INCLUDED_AAAA79D3 */
