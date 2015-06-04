#ifndef TOT_H_HEADER_INCLUDED_AA9BEC2E
#define TOT_H_HEADER_INCLUDED_AA9BEC2E

#include "Section.h"

class Descriptor;

//##ModelId=55640E9C0019
class TOT : public Section
{
  public:
    //##ModelId=55640EA801B6
    TOT();

    //##ModelId=55640EAC00FC
    TOT(uint8_t* data, uint16_t len);

    //##ModelId=55640EAF034C
    virtual ~TOT();

    virtual bool joinTo(SectionFactory* sf);

    virtual void resolved();

    virtual void getDetail(uint8_t* data, uint16_t len);

    //##ModelId=55640EE902E4
    uint8_t UTC_time[5];
    //##ModelId=55640F0801E8
    uint16_t descriptors_loop_length;
    //##ModelId=55640F1D0376
    std::list<Descriptor*> desc_list;
    //##ModelId=55640F340294
    uint32_t crc32;
};



#endif /* TOT_H_HEADER_INCLUDED_AA9BEC2E */
