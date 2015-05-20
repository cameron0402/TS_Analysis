#ifndef SECTIONFACTORY_H_HEADER_INCLUDED_AAAA5AA3
#define SECTIONFACTORY_H_HEADER_INCLUDED_AAAA5AA3
class Section;

#include "../def.h"

//##ModelId=55554FBB02A9
class SectionFactory
{
    
  public:
    //##ModelId=5555501D00F6
    void add(Section* sc);

    //##ModelId=555550B4016A
    virtual Section* createSectoin(int32_t type, void* data, int32_t len);

    //##ModelId=5555977903C2
    static SectionFactory* GetInstance();

    //##ModelId=55554FD7004E
    std::list<Section*> slist;
  private:
    //##ModelId=555597630041
    SectionFactory();

    //##ModelId=555597B201DB
    static SectionFactory* _instance;
};



#endif /* SECTIONFACTORY_H_HEADER_INCLUDED_AAAA5AA3 */
