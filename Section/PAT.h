#ifndef PAT_H_HEADER_INCLUDED_AAAA2BEF
#define PAT_H_HEADER_INCLUDED_AAAA2BEF
#include "Section.h"
#include <list>

//##ModelId=55555D8302B9
class PAT : public Section
{
  public:
    //##ModelId=555563C40216
    class ProgInfo
    {
      public:
        //##ModelId=555563E60300
        uint16_t program_number;
        // network_PID if program_number == 0
        //##ModelId=555563FF0039
        uint16_t program_map_PID;
    };

    //##ModelId=55555EB90262
    PAT();

    //##ModelId=55555EC7002C
    PAT(uint8_t* data, uint16_t len);

    virtual ~PAT();

    //##ModelId=5555627B01B5
    std::list<ProgInfo> prog_list;
};



#endif /* PAT_H_HEADER_INCLUDED_AAAA2BEF */
