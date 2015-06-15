#include "TOT.h"
#include "SectionFactory.h"
#include "../Descriptor/Descriptor.h"
#include "../Descriptor/DVBDesc/DescFactory.h"

//##ModelId=55640EA801B6
TOT::TOT()
{
}

//##ModelId=55640EAC00FC
TOT::TOT(uint8_t* data, uint16_t len, uint32_t crc)
    : Section(data, len),
      descriptors_loop_length(((data[8] & 0xF) << 8) | data[9]),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    if(crc != 0xFFFFFFFF)
    {
        if(crc != crc32)
            throw CrcErr(CrcErr::CTOT);
    }
    memcpy(UTC_time, data + 3, 5);
}

//##ModelId=55640EAF034C
TOT::~TOT()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

bool TOT::joinTo(SectionFactory* sf)
{
    if(sf->tot != NULL)
        return false;
    
    sf->tot = this;
    return true;
}

void TOT::getDetail(uint8_t* data, uint16_t len)
{
    int index = 10;
    DescFactory des_fac;
    while(index < len - 4)
    {
        Descriptor* des = des_fac.createDesc(data[index], data + index);
        desc_list.push_back(des);
        index += des->length + 2;
    }
}

void TOT::resolved()
{
    TiXmlElement* tmp;
    char arr[32] = {0};

    Section::resolved();
    xml->SetAttribute("table_id", table_id);

    utc_to_ymdhms(UTC_time, arr);
    tmp = new TiXmlElement("UTC_time");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", descriptors_loop_length);
    tmp = new TiXmlElement("descriptors_loop_length");
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

