#include "SectionFactory.h"
#include "Section.h"

SectionFactory* SectionFactory::_instance = NULL;

//##ModelId=5555501D00F6
void SectionFactory::add(Section* sc)
{
}

//##ModelId=555550B4016A
Section* SectionFactory::createSectoin(int32_t type, void* data, int32_t len)
{
    return NULL;
}

//##ModelId=5555977903C2
SectionFactory* SectionFactory::GetInstance()
{
    if(_instance == NULL)
    {
        _instance = new SectionFactory;
    }
    return _instance;
}

//##ModelId=555597630041
SectionFactory::SectionFactory()
{
}

