#include "ShortEventDesc.h"

//##ModelId=555AABE400CA
ShortEventDesc::ShortEventDesc()
{
}

//##ModelId=555AABF40041
ShortEventDesc::ShortEventDesc(uint8_t* data)
    : Descriptor(data),
      event_name_length(data[5]),
      text_length(data[6 + event_name_length])
{
    memcpy(ISO6392_language, data + 2, 3);
    event_name = new uint8_t[event_name_length];
    memcpy(event_name, data + 6, event_name_length);
    text = new uint8_t[text_length];
    memcpy(text, data + 7 + event_name_length, text_length);
}

//##ModelId=555AAC0C03A9
ShortEventDesc::~ShortEventDesc()
{
    delete []event_name;
    delete []text;
}

