#ifndef CAT_H_HEADER_INCLUDED_AAAA5B12
#define CAT_H_HEADER_INCLUDED_AAAA5B12
#include "Section.h"
#include <vector>
class Descriptor;

//##ModelId=555589B50379
class CAT : public Section
{
  public:
    //##ModelId=55558B3703CA
    CAT();

    //##ModelId=55558B3E03C8
    CAT(uint8_t* data, uint16_t len);

    virtual ~CAT();

    //##ModelId=55558B6C03A8
    std::list<Descriptor*> desc_list;
};



#endif /* CAT_H_HEADER_INCLUDED_AAAA5B12 */
