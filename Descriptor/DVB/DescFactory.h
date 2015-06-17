#ifndef DESCFACTORY_H_HEADER_INCLUDED_AAA7A823
#define DESCFACTORY_H_HEADER_INCLUDED_AAA7A823
#include "../../def.h"
class Descriptor;

//##ModelId=5558565E0386
class DescFactory
{
  public:
    //##ModelId=55585690038B
    virtual Descriptor* createDesc(uint8_t type, uint8_t* data);

};

#endif /* DESCFACTORY_H_HEADER_INCLUDED_AAA7A823 */
