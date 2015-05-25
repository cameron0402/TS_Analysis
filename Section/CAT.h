#ifndef CAT_H_HEADER_INCLUDED_AAAA6611
#define CAT_H_HEADER_INCLUDED_AAAA6611
#include "Section.h"
class Descriptor;

//##ModelId=555589B50379
class CAT : public Section
{
  public:
    //##ModelId=55558B3703CA
    CAT();

    //##ModelId=55558B3E03C8
    CAT(uint8_t* data, uint16_t len);
    //##ModelId=555828DD0014
    virtual ~CAT();
    virtual bool joinTo(SectionFactory* sf);
    bool operator ==(const CAT& ct);

    //##ModelId=5562980E020A
    uint8_t version_number;
    //##ModelId=55629817021A
    bool current_next_indicator;
    //##ModelId=5562984E03E4
    uint8_t section_number;
    //##ModelId=556298570363
    uint8_t last_section_number;
    //##ModelId=55558B6C03A8
    std::list<Descriptor*> desc_list;
    
    //##ModelId=5562991F024A
    uint32_t crc32;
};



#endif /* CAT_H_HEADER_INCLUDED_AAAA6611 */
