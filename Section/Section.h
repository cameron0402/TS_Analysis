#ifndef SECTOIN_H_HEADER_INCLUDED_AAAA3049
#define SECTOIN_H_HEADER_INCLUDED_AAAA3049
#include "SectionFactory.h"
#include "../def.h"

//##ModelId=5555516C0171
class Section
{
  public:
    Section();
    Section(uint8_t* data, uint16_t len);
    virtual ~Section();
    //##ModelId=5555540B00A0
    virtual bool joinTo(SectionFactory& sf);

    //##ModelId=555561E1025F
    virtual void resolved();

    // table_id
    //##ModelId=555551840342
    uint8_t table_id;
    // section_syntax_indicator
    //##ModelId=555551BF011A
    bool syntax_indicator;
    // private_indicator
    //##ModelId=555551E20187
    bool private_indicator;
    // section_length
    //##ModelId=555552030016
    uint16_t length;
    // table_id_extension 
    // transport_stream_id for PAT section 
    //##ModelId=5555523F02DB
    uint16_t extension;
    // version_number
    //##ModelId=555552E203A2
    uint8_t version;
    // current_next_indicator
    //##ModelId=5555531C0031
    bool current_next;
    // section_number
    //##ModelId=5555534900FD
    uint8_t number;
    // last_section_number
    //##ModelId=55555372015F
    uint8_t last_number;
    // CRC_32
    //##ModelId=5555539A0318
    uint32_t crc32;
};



#endif /* SECTOIN_H_HEADER_INCLUDED_AAAA3049 */
