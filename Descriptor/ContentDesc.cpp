#include "ContentDesc.h"

ContentDesc::ContentInfo::ContentInfo()
{

}

ContentDesc::ContentInfo::ContentInfo(uint8_t* data)
    : content_nibble_level_1(data[0] >> 4),
      content_nibble_level_2(data[0] & 0xF),
      user_nibble_1(data[1] >> 4),
      user_nibble_2(data[1] & 0xF)
{

}

ContentDesc::ContentInfo::~ContentInfo()
{

}

//##ModelId=555AF3270376
ContentDesc::ContentDesc()
{
}

//##ModelId=555AF32E0325
ContentDesc::ContentDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    ContentInfo* tmp;
    while(index < length + 2)
    {
        tmp = new ContentInfo(data + index);
        content_list.push_back(tmp);
        index += 2;
    }
}

//##ModelId=555AF34201EF
ContentDesc::~ContentDesc()
{
    std::list<ContentInfo*>::iterator cit;
    for(cit = content_list.begin(); cit != content_list.end(); ++cit)
    {
        delete (*cit);
    }
    content_list.clear();
}

void ContentDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("content_descriptor");

    if(!content_list.empty())
    {
        std::list<ContentInfo*>::iterator cit;

        for(cit = content_list.begin(); cit != content_list.end(); ++cit)
        {
            tmp = new TiXmlElement("Content");

            TiXmlElement* tms;
            sprintf(arr, "0x%x", (*cit)->content_nibble_level_1);
            tms = new TiXmlElement("content_nibble_level_1");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*cit)->content_nibble_level_2);
            tms = new TiXmlElement("content_nibble_level_2");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*cit)->user_nibble_1);
            tms = new TiXmlElement("user_nibble_1");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*cit)->user_nibble_2);
            tms = new TiXmlElement("user_nibble_2");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            xml->LinkEndChild(tmp);
        }
 
    }
    
}

