#include "PMT.h"
#include "SectionFactory.h"
#include "../Descriptor/DescFactory.h"
#include "../Descriptor/Descriptor.h"

//##ModelId=55556B720001
PMT::PMT()
{
}

//##ModelId=55556B820369
PMT::PMT(uint8_t* data, uint16_t len)
    : Section(data, len),
      program_number((data[3] << 8) | data[4]), 
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      PCR_PID(((data[8] & 0x1F) << 8) | data[9]),
      program_info_length(((data[10] & 0x0F) << 8) | data[11]),
      desc_list(),
      stream_list(),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
}

//##ModelId=5558288B00A9
PMT::~PMT()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();

    std::list<StreamInfo*>::iterator sit;
    for(sit = stream_list.begin(); sit != stream_list.end(); ++sit)
    {
        delete (*sit);
    }
    stream_list.clear();
}

//##ModelId=555D7D58002F
PMT::StreamInfo::StreamInfo()
{
}

//##ModelId=555D7D6A03E1
PMT::StreamInfo::StreamInfo(uint8_t* data)
    : type(data[0]),
      elem_PID(((data[1] & 0x1F) << 8) | data[2]),
      info_length(((data[3] & 0x0F) << 8) | data[4])    
{
    int index = 0;
    uint8_t* sub_data = data + 5;
    DescFactory des_fac;
    while(index < info_length)
    {
        Descriptor* des = des_fac.createDesc(sub_data[index], sub_data + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }
}

//##ModelId=555D7D6D016C
PMT::StreamInfo::~StreamInfo()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

bool PMT::joinTo(SectionFactory* sf)
{
    /*std::list<PMT*>::iterator pit;
    for(pit = sf->pmt_list.begin(); pit != sf->pmt_list.end(); ++pit)
    {
    if(*(*pit) == *this)
    return false;
    }
    sf->pmt_list.push_back(this);
    return true;*/
    std::pair<std::set<PMT*, cmp_secp<PMT>>::iterator, bool> ret;
    ret = sf->pmt_list.insert(this);
    return ret.second;
}

bool PMT::operator==(const PMT& pt)
{
    return program_number == pt.program_number &&
           version_number == pt.version_number &&
           section_number == pt.section_number;
}

bool PMT::operator<(const PMT& pt)
{
    if(program_number < pt.program_number)
        return true;
    else if(program_number == pt.program_number)
    {
        if(version_number < pt.version_number)
            return true;
        else if(version_number == pt.version_number)
        {
            if(section_number < pt.section_number)
                return true;
        }
    }
    return false;
}

void PMT::getDetail(uint8_t* data, uint16_t len)
{
    int index = 0;
    uint8_t* pd = data + 12;
    DescFactory des_fac;
    while(index < program_info_length)
    {
        Descriptor* des = des_fac.createDesc(pd[index], pd + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }

    index = 12 + program_info_length;
    while(index < len - 4)
    {
        StreamInfo* si = new StreamInfo(data + index);
        index += si->info_length + 5;
        stream_list.push_back(si);
    }
}

void PMT::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Section::resolved();
    xml->SetAttribute("program_number", program_number);
    xml->SetAttribute("version_number", version_number);
    xml->SetAttribute("section_number", section_number);

    sprintf(arr, "0x%x", program_number);
    tmp = new TiXmlElement("program_number");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

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

    sprintf(arr, "0x%x", PCR_PID);
    tmp = new TiXmlElement("PCR_PID");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", program_info_length);
    tmp = new TiXmlElement("program_info_length");
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

    if(!stream_list.empty())
    {
        std::list<StreamInfo*>::iterator sit;
        for(sit = stream_list.begin(); sit != stream_list.end(); ++sit)
        {
            tmp = new TiXmlElement("Stream");
            tmp->SetAttribute("stream_type", (*sit)->type);
            tmp->SetAttribute("elementary_PID", (*sit)->elem_PID);
            tmp->SetAttribute("ES_info_length", (*sit)->info_length);
            if(!(*sit)->desc_list.empty())
            {
                TiXmlElement* tms = new TiXmlElement("Descriptors");
                std::list<Descriptor*>::iterator sdit;
                for(sdit = (*sit)->desc_list.begin(); sdit != (*sit)->desc_list.end(); ++sdit)
                {
                    (*sdit)->resolved();
                    tms->LinkEndChild((*sdit)->xml);
                }
                tmp->LinkEndChild(tms);
            }  
            xml->LinkEndChild(tmp);
        }
    }
    
    sprintf(arr, "0x%x", crc32);
    tmp = new TiXmlElement("CRC32");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);
}



