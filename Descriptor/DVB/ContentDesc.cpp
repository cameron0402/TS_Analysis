#include "ContentDesc.h"

/* EIT 内容类型列表 */
const char* const eit_content_table[16][16] = 
{
    "",                 "",                             "",                  "",                  "",                   "",            "",              "",            "",         "",         "",              "",               "",     "",  "",  "",
    "电影/电视剧/戏剧", "侦探/恐怖",                    "冒险/战争",         "科幻",              "喜剧",               "肥皂剧",      "言情",          "古典/历史",   "",         "",         "",              "",               "",     "",  "",  "", 
    "新闻时事",         "新闻/天气预报",                "新闻杂志",          "资料",              "讨论/访谈/辩论",     "",            "",              "",            "",         "",         "",              "",               "",     "",  "",  "", 
    "表演/游戏",        "智力游戏/智力竞赛",            "杂技",              "脱口秀",            "",                   "",            "",              "",            "",         "",         "",              "",               "",     "",  "",  "", 
    "综合体育",         "特别节目（奥运会、世界杯等）", "体育杂志",          "足球/篮球/排球",    "乒乓球/羽毛球/网球", "团体性运动",  "田径",          "自行车/赛车", "水上运动", "冬季运动", "马术",          "武术/拳击/摔跤", "棋牌", "",  "",  "", 
    "青年少儿节目",     "幼儿节目",                     "少儿节目",          "青年节目",          "信息/教育",          "卡通/木偶戏", "",              "",            "",         "",         "",              "",               "",     "",  "",  "", 
    "音乐/舞蹈",        "流行",                         "严肃音乐/古典音乐", "民俗音乐/民族音乐", "爵士乐",             "歌舞剧/歌剧", "芭蕾舞",        "戏曲/曲艺",   "",         "",         "",              "",               "",     "",  "",  "", 
    "文化艺术",         "表演艺术",                     "高雅艺术",          "",                  "大众文化/传统艺术",  "文学",        "电影/电视文化", "",            "",         "新媒体",   "艺术/文化杂志", "时尚",           "",     "",  "",  "", 
    "社会/政治/经济",   "杂志/报道/资讯/证券",          "经济/社会咨询",     "名人专题",          "",                   "",            "",              "",            "",         "",         "",              "",               "",     "",  "",  "", 
    "教育/科学/专题",   "自然/动物/环境",               "技术/自然科学",     "医疗/生理/心理",    "探险",               "社会科学",    "继续教育",      "语言",        "",         "",         "",              "",               "",     "",  "",  "", 
    "休闲/业余爱好",    "旅游",                         "手工",              "车趣",              "健身",               "烹饪",        "广告/购物",     "园艺",        "",         "",         "",              "",               "",     "",  "",  "", 
    "",                 "",                             "",                  "",                  "",                   "",            "",              "",            "",         "",         "",              "",               "",     "",  "",  "",
    "",                 "",                             "",                  "",                  "",                   "",            "",              "",            "",         "",         "",              "",               "",     "",  "",  "",
    "",                 "",                             "",                  "",                  "",                   "",            "",              "",            "",         "",         "",              "",               "",     "",  "",  "",
    "",                 "",                             "",                  "",                  "",                   "",            "",              "",            "",         "",         "",              "",               "",     "",  "",  "",
    "",                 "",                             "",                  "",                  "",                   "",            "",              "",            "",         "",         "",              "",               "",     "",  "",  ""
};

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

