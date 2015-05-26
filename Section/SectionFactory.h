#ifndef SECTIONFACTORY_H_HEADER_INCLUDED_AAAA5AA3
#define SECTIONFACTORY_H_HEADER_INCLUDED_AAAA5AA3

#include "../def.h"
class Section;
class PMT;
class PAT;
class NIT;
class CAT;
class BAT;
class SDT;
class EIT;
class TDT;
class TOT;
class SectionData;

//##ModelId=55554FBB02A9
class SectionFactory
{
  public:
    //##ModelId=5555501D00F6
    bool addSection(Section* section);

    //##ModelId=555550B4016A
    virtual Section* createSectoin(SectionData* raw_section);

    //##ModelId=5555977903C2
    static SectionFactory* GetInstance();

    void sectionGather(uint8_t* ts_packet);

    virtual ~SectionFactory();

    //##ModelId=55554FD7004E
    std::list<PMT*> pmt_list;
    //##ModelId=555EC4BE00E8
    PAT* pat;
  
    //##ModelId=555EC4CC023F
    std::list<NIT*> nit_list;
  
    //##ModelId=555EC4EC006E
    std::list<CAT*> cat_list;

    std::list<BAT*> bat_list;

    std::list<SDT*> sdt_list;

    std::list<EIT*> eit_list;

    TDT* tdt;

    TOT* tot;
  
    //##ModelId=555EC50E007F
    SectionData* raw_section;
  private:
    //##ModelId=555597630041
    SectionFactory();

    //##ModelId=555597B201DB
    static SectionFactory* _instance;
};



#endif /* SECTIONFACTORY_H_HEADER_INCLUDED_AAAA5AA3 */
