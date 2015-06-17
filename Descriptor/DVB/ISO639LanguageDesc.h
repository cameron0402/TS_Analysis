#ifndef ISO639LANGUAGEDESC_H_HEADER_INCLUDED_AAA6F495
#define ISO639LANGUAGEDESC_H_HEADER_INCLUDED_AAA6F495
#include "../Descriptor.h"

// descriptor_tag = 0x0A
//##ModelId=555938CA0096
class ISO639LanguageDesc : public Descriptor
{
  public:
    //##ModelId=555938E30314
    class LanguageInfo
    {
    public:
        LanguageInfo();
        LanguageInfo(uint8_t* data);
        ~LanguageInfo();

        uint8_t lang[3];
        uint8_t audio_type;
    };
    ISO639LanguageDesc();

    //##ModelId=555938F30225
    ISO639LanguageDesc(uint8_t* data);

    //##ModelId=555939280014
    virtual ~ISO639LanguageDesc();

    virtual void resolved();

    std::list<LanguageInfo*> lang_list;
};



#endif /* ISO639LANGUAGEDESC_H_HEADER_INCLUDED_AAA6F495 */
