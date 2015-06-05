#ifndef SECTION_H_HEADER_INCLUDED_AA9D5029
#define SECTION_H_HEADER_INCLUDED_AA9D5029

#include "../def.h"

class SectionFactory;
//##ModelId=5555516C0171
class Section
{
  public:
    //##ModelId=5555540B00A0
    virtual bool joinTo(SectionFactory* sf);

    //##ModelId=555561E1025F
    virtual void resolved();

    virtual void getDetail(uint8_t* data, uint16_t len);

    //##ModelId=5555A63E015D
    Section();

    //##ModelId=5555A64603C5
    Section(uint8_t* data, uint16_t len);

    //##ModelId=5558283C00A1
    virtual ~Section();

    //##ModelId=555551840342
    uint8_t table_id;
    //##ModelId=555551BF011A
    bool syntax_indicator;
    //##ModelId=555551E20187
    bool private_indicator;
    //##ModelId=555552030016
    uint16_t length;

    //for resolved
    TiXmlElement* xml;

};

template<class T>
struct cmp_secp
{
    bool operator()(T* secp1, T* secp2) const 
    {
        return (*secp1) < (*secp2);
    }
};



#endif /* SECTION_H_HEADER_INCLUDED_AA9D5029 */
