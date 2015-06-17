#ifndef SECTIONFACTORY_H_HEADER_INCLUDED_AAAA5AA3
#define SECTIONFACTORY_H_HEADER_INCLUDED_AAAA5AA3

#include "../def.h"
#include "PSI_SI/BAT.h"
#include "PSI_SI/CAT.h"
#include "PSI_SI/EIT.h"
#include "PSI_SI/NIT.h"
#include "PSI_SI/PAT.h"
#include "PSI_SI/PMT.h"
#include "PSI_SI/SDT.h"
#include "PSI_SI/TDT.h"
#include "PSI_SI/TOT.h"

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

    void sectionGather(int pid, uint8_t* ts_packet);

    virtual ~SectionFactory();

    //##ModelId=55554FD7004E
    std::set<PMT*, cmp_secp<PMT>> pmt_list;
    //##ModelId=555EC4BE00E8
    PAT* pat;
  
    //##ModelId=555EC4CC023F
    std::set<NIT*, cmp_secp<NIT>> nit_list;
  
    //##ModelId=555EC4EC006E
    std::set<CAT*, cmp_secp<CAT>> cat_list;

    std::list<BAT*> bat_list;

    std::set<SDT*, cmp_secp<SDT>> sdt_list;

    std::set<EIT*, cmp_secp<EIT>> eit_list;

    TDT* tdt;

    TOT* tot;

    SectionData* raw_sarr[MAX_PID_NUM];
  private:
    //##ModelId=555597630041
    SectionFactory();

    //##ModelId=555597B201DB
    static SectionFactory* _instance;
};



#endif /* SECTIONFACTORY_H_HEADER_INCLUDED_AAAA5AA3 */
