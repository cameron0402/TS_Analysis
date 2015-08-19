#ifndef SECTION_H_HEADER_INCLUDED_AA9D5029
#define SECTION_H_HEADER_INCLUDED_AA9D5029

#include "../def.h"

class TSFactory;
//##ModelId=5555516C0171
class Section
{
  public:

    virtual bool joinTo(TSFactory* sf);
    virtual void resolved();
    virtual void getDetail();

    Section(uint8_t* data, uint16_t len, uint32_t crc = 0xFFFFFFFF);
    virtual ~Section();

    uint8_t table_id;
    bool syntax_indicator;
    bool private_indicator;
    uint16_t length;

    uint8_t* raw_data;
    //for resolved
    TiXmlElement* xml;

};

#endif /* SECTION_H_HEADER_INCLUDED_AA9D5029 */
