#ifndef PAT_H_HEADER_INCLUDED_AAAA7CE5
#define PAT_H_HEADER_INCLUDED_AAAA7CE5
#include "Section.h"

//##ModelId=55555D8302B9
class PAT : public Section
{
  public:
    //##ModelId=555563C40216
    class ProgInfo
    {
      public:
        //##ModelId=555D78E90265
        ProgInfo();

        //##ModelId=555563E60300
        //##ModelId=555D78EB0320
        ProgInfo(uint8_t* data);

        
        //##ModelId=555D78EE02D5
        virtual ~ProgInfo();

        uint16_t program_number;
        // network_PID if program_number == 0
        //##ModelId=555563FF0039
        uint16_t program_map_PID;
    };

    //##ModelId=55555EB90262
    PAT();

    //##ModelId=55555EC7002C
    PAT(uint8_t* data, uint16_t len);
    //##ModelId=55582871031A
    virtual ~PAT();


    //##ModelId=5555627B01B5
    std::list<ProgInfo*> prog_list;
};



#endif /* PAT_H_HEADER_INCLUDED_AAAA7CE5 */
