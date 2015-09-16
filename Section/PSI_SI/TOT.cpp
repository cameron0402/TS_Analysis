#include "TOT.h"
#include "../../TSAnalysis/TSFactory.h"
#include "../../Descriptor/Descriptor.h"
#include "../../Descriptor/DVB/DescFactory.h"

TOT::TOT(uint8_t* data, uint16_t len, uint32_t crc)
    : Section(data, len),
      descriptors_loop_length(((data[8] & 0xF) << 8) | data[9]),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    if(crc != 0xFFFFFFFF)
    {
        if(crc != crc32)
            throw new CrcErr(CrcErr::CTOT);
    }
    memcpy(UTC_time, data + 3, 5);
}

TOT::~TOT()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

bool TOT::joinTo(TSFactory* sf)
{
    if(sf->tot != NULL)
        return false;
    
    getDetail();
    sf->tot = this;
    return true;
}

void TOT::getDetail()
{
    if(raw_data == NULL)
        return ;

    int index = 10;
    DescFactory des_fac;
    while(index < length - 4)
    {
        Descriptor* des = des_fac.createDesc(raw_data[index], raw_data + index);
        desc_list.push_back(des);
        index += des->length + 2;
    }

    delete []raw_data;
    raw_data = NULL;
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

