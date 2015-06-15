#include "CAT.h"
#include "SectionFactory.h"
#include "../Descriptor/Descriptor.h"
#include "../Descriptor/DVBDesc/DescFactory.h"

//##ModelId=55558B3703CA
CAT::CAT()
{
}

//##ModelId=55558B3E03C8
CAT::CAT(uint8_t* data, uint16_t len, uint32_t crc) 
    : Section(data, len),
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      desc_list(),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    if(table_id != 0x1)
        throw CatErr(CatErr::CTID);

    if(crc != 0xFFFFFFFF)
    {
        if(crc != crc32)
            throw CrcErr(CrcErr::CCAT);
    }
}

CAT::~CAT()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}


bool CAT::joinTo(SectionFactory* sf)
{
    std::pair<std::set<CAT*, cmp_secp<CAT>>::iterator, bool> ret;
    ret = sf->cat_list.insert(this);
    return ret.second;
}

void CAT::getDetail(uint8_t* data, uint16_t len)
{
    int index = 8;
    DescFactory des_fac;
    while(index < len - 4)
    {
        Descriptor* des = des_fac.createDesc(data[index], data + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }
}

bool CAT::operator==(const CAT& ct)
{
    return version_number == ct.version_number &&
           section_number == ct.section_number &&
           current_next_indicator == ct.current_next_indicator;
    //return crc32 == ct.crc32;
}

bool CAT::operator<(const CAT& ct)
{
    if(version_number < ct.version_number)
        return true;
    else if(version_number == ct.version_number)
    {
        if(section_number < ct.section_number)
            return true;
        else if(section_number == ct.section_number)
        {
            if(current_next_indicator < ct.current_next_indicator)
                return true;
        }
    }

    return false;
}

void CAT::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Section::resolved();
    xml->SetAttribute("version_number", version_number);
    xml->SetAttribute("section_number", section_number);

    sprintf(arr, "0x%x", version_number);
    tmp = new TiXmlElement("version_number");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", current_next_indicator);
    tmp = new TiXmlElement("current_next_indicator");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", section_number);
    tmp = new TiXmlElement("section_number");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", last_section_number);
    tmp = new TiXmlElement("last_section_number");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    if(!desc_list.empty())
    {
        tmp = new TiXmlElement("Descriptors");
        std::list<Descriptor*>::iterator dit;
        for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
        {
            (*dit)->resolved();
            tmp->LinkEndChild((*dit)->xml);
        }
        xml->LinkEndChild(tmp);
    }

    sprintf(arr, "0x%x", crc32);
    tmp = new TiXmlElement("CRC32");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);
}

