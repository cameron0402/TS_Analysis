#ifndef ISO639LANGUAGEDESC_H_HEADER_INCLUDED_AAA6F495
#define ISO639LANGUAGEDESC_H_HEADER_INCLUDED_AAA6F495
#include "Descriptor.h"

// descriptor_tag = 0x0A
//##ModelId=555938CA0096
class ISO639LanguageDesc : public Descriptor
{
  public:
    //##ModelId=555938E30314
    ISO639LanguageDesc();

    //##ModelId=555938F30225
    ISO639LanguageDesc(uint8_t* data);

    //##ModelId=555939280014
    virtual ~ISO639LanguageDesc();

    //##ModelId=55593C7F0153
    std::list<std::vector<char>> lang_list;
    //##ModelId=55593D380024
    uint8_t audio_type;
};



#endif /* ISO639LANGUAGEDESC_H_HEADER_INCLUDED_AAA6F495 */
