#include "SectionFactory.h"
#include "Section.h"
#include "PAT.h"
#include "PMT.h"
#include "CAT.h"
#include "NIT.h"

SectionFactory* SectionFactory::_instance = NULL;

//##ModelId=5555501D00F6
void SectionFactory::add(Section* sc)
{
}

//##ModelId=555550B4016A
Section* SectionFactory::createSectoin(int32_t type, uint8_t* data, int32_t len)
{
    switch(type)
    {
        case 0x00: return new PAT(data, len);
        case 0x01: return new CAT(data, len);
        case 0x10:
        {
            if(data[0] == 0x40 || data[1] == 0x41) 
                return new NIT(data, len);
            else 
                break;
        }
    }
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

