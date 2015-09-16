#include "PAT.h"
#include "../../TSAnalysis/TSFactory.h"
#include "../../TSAnalysis/TSData.h"

PAT::PAT(uint8_t* data, uint16_t len, uint32_t crc) 
    : Section(data, len),
      transport_stream_id((data[3] << 8) | data[4]), 
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      prog_list(),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    if(table_id != 0x0)
        throw new PatErr(PatErr::PTID);

    if(crc != 0xFFFFFFFF)
    {
        if(crc != crc32)
            throw new CrcErr(CrcErr::CPAT);
    }
}

PAT::~PAT()
{
    std::list<ProgInfo*>::iterator pit;
    for(pit = prog_list.begin(); pit != prog_list.end(); ++pit)
    {
        delete (*pit);
    }
    prog_list.clear();
}

void PAT::getDetail()
{
    if(raw_data == NULL)
        return ;

    int index = 8;
    while(index < length - 4)
    {
        ProgInfo* pi = new ProgInfo(raw_data + index);
        prog_list.push_back(pi);
        index += 4;
    }

    delete []raw_data;
    raw_data = NULL;
}

bool PAT::joinTo(TSFactory* sf)
{
    if(sf->pat == NULL)
    {
        this->getDetail();
        std::list<ProgInfo*>::iterator pit;
        for(pit = prog_list.begin(); pit != prog_list.end(); ++pit)
        {
            uint16_t pid = (*pit)->program_map_PID;
            if(sf->raw_sarr[pid] != NULL)
            {
                delete sf->raw_sarr[pid];
            }
            sf->raw_sarr[pid] = new TSData(pid);
            sf->raw_sarr[pid]->type.type = TS_TYPE_SECTION;
            strcpy(sf->raw_sarr[pid]->type.sdes, "PMT");
        }
        sf->pat = this;
        return true;
    }
    return false;
}

void PAT::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Section::resolved();
    xml->SetAttribute("transport_stream_id", transport_stream_id);
    xml->SetAttribute("version_number", version_number);
    xml->SetAttribute("section_number", section_number);

    sprintf(arr, "0x%x", transport_stream_id);
    tmp = new TiXmlElement("transport_stream_id");
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

    tmp = new TiXmlElement("Program_Info");
    tmp->SetAttribute("program quantity", prog_list.size());
    std::list<ProgInfo*>::iterator pit;
    for(pit = prog_list.begin(); pit != prog_list.end(); ++pit)
    {
        TiXmlElement* stmp;
        if((*pit)->program_number != 0x0)
        {
            stmp = new TiXmlElement("Program");
            stmp->SetAttribute("Program_number", (*pit)->program_number);
            stmp->SetAttribute("PMT_PID", (*pit)->program_map_PID);
        }
        else
        {
            stmp = new TiXmlElement("Network");
            stmp->SetAttribute("Program_number", (*pit)->program_number);
            stmp->SetAttribute("NIT_PID", (*pit)->program_map_PID);
        }
        tmp->LinkEndChild(stmp);       
    }
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", crc32);
    tmp = new TiXmlElement("CRC32");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);
}

bool PAT::operator==(const PAT& pt)
{
    return transport_stream_id == pt.transport_stream_id &&
           version_number == pt.version_number &&
           section_number == pt.section_number;
    //return crc32 == pt.crc32;
}