#include "PMT.h"
#include "../../TSAnalysis/TSFactory.h"
#include "../../TSAnalysis/TSData.h"
#include "../DSMCC/DsmccSection.h"
#include "../../Descriptor/Descriptor.h"
#include "../../Descriptor/DVB/DescFactory.h"
#include "../../Descriptor/DVB/CADesc.h"

PMT::PMT(uint8_t* data, uint16_t len, uint32_t crc)
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
    if(crc != 0xFFFFFFFF)
    {
        if(crc != crc32)
            throw new CrcErr(CrcErr::CPMT);
    }
}

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

PMT::StreamInfo::~StreamInfo()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

bool PMT::joinTo(TSFactory* sf)
{
    bool upd = false;
    std::set<PMT*, cmp_secp<PMT>>::iterator 
        fit = sf->pmt_list.find(this);
    if(fit == sf->pmt_list.end())
    {
        sf->pmt_list.insert(this);
        this->getDetail();
    }
    else
    {
        if(this->version_number <= (*fit)->version_number)
            return false;

        PMT* pt = (*fit);
        pt->version_number = this->version_number;
        pt->crc32 = this->crc32;
        upd = true;
    }
    
    if(!upd)
    {
        //set the dsmcc section
        ESGInfo* ei = NULL;
        std::list<StreamInfo*>::iterator sit;
        for(sit = stream_list.begin(); sit != stream_list.end(); ++sit)
        {
            uint16_t pid = (*sit)->elem_PID;
            if((*sit)->type == 0x0B)
            {
                if(sf->raw_sarr[pid] == NULL)
                {
                    sf->raw_sarr[pid] = sf->createTSdata(pid, TS_TYPE_SECTION, "13818-6 type B");
                }
                else
                {
                    sf->raw_sarr[pid]->Reset();
                    sf->raw_sarr[pid]->type.type = TS_TYPE_SECTION;
                    strcpy(sf->raw_sarr[pid]->type.sdes, "13818-6 type B");
                }
                
                if(ei == NULL)
                    ei = new ESGInfo(program_number);

                if(ei != NULL)
                    ei->pid_list.push_back(pid);
            }
            else
            {
                if(sf->raw_sarr[pid] == NULL)
                {
                    sf->raw_sarr[pid] = sf->createTSdata(pid, TS_TYPE_PES, "未知类型");
                }
            }
        }

        if(ei != NULL)
            sf->esg_list.push_back(ei);

        //set the streams pid info
        std::list<ProgInfo*>::iterator pit = sf->pat->prog_list.begin();
        for(; pit != sf->pat->prog_list.end(); ++pit)
        {
            if(program_number == (*pit)->program_number)
            {
                (*pit)->setInfo(this);
                std::list<Stream*>::iterator sit = (*pit)->stream_list.begin();
                for(; sit != (*pit)->stream_list.end(); ++sit)
                {
                    int pid = (*sit)->stream_pid;
                    if((*sit)->scrambling)
                        sf->raw_sarr[pid]->scrambling_flag = true;

                    strcpy(sf->raw_sarr[pid]->type.sdes, (*sit)->stream_type->sdes);
                    if((*sit)->stream_type->type == TS_TYPE_VID)
                        strcat(sf->raw_sarr[pid]->type.sdes, " 视频");
                    else if((*sit)->stream_type->type == TS_TYPE_AUD)
                        strcat(sf->raw_sarr[pid]->type.sdes, " 音频");
                }
                break;
            }
        }

        //set the ECM pid info
        std::list<Descriptor*>::iterator dit = desc_list.begin();
        for(; dit != desc_list.end(); ++dit)
        {
            if((*dit)->tag == 0x09)
            {
                uint16_t ecm_pid = ((CADesc*)(*dit))->CA_PID;
                if(sf->raw_sarr[ecm_pid] == NULL)
                {
                    sf->raw_sarr[ecm_pid] = sf->createTSdata(ecm_pid, TS_TYPE_PES, "ECM");
                }
                else
                {
                    strcpy(sf->raw_sarr[ecm_pid]->type.sdes, "ECM");
                }
            }
        }
    }
    
    return true;
}

bool PMT::operator==(const PMT& pt)
{
    return program_number == pt.program_number &&
           section_number == pt.section_number;
}

bool PMT::operator<(const PMT& pt)
{
    if(program_number < pt.program_number)
        return true;
    else if(program_number == pt.program_number)
    {
        if(section_number < pt.section_number)
            return true;
    }
    return false;
}

void PMT::getDetail()
{
    if(raw_data == NULL)
        return ;

    int index = 0;
    uint8_t* pd = raw_data + 12;
    DescFactory des_fac;
    while(index < program_info_length)
    {
        Descriptor* des = des_fac.createDesc(pd[index], pd + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }

    index = 12 + program_info_length;
    while(index < length - 1)
    {
        StreamInfo* si = new StreamInfo(raw_data + index);
        index += si->info_length + 5;
        stream_list.push_back(si);
    }

    delete []raw_data;
    raw_data = NULL;
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



