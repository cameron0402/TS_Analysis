#include "NIT.h"
#include "../../TSAnalysis/TSFactory.h"
#include "../../Descriptor/Descriptor.h"
#include "../../Descriptor/DVB/DescFactory.h"

NIT::NIT(uint8_t* data, uint16_t len, uint32_t crc)
    : Section(data, len),
      network_id((data[3] << 8) | data[4]), 
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      network_descriptors_length(((data[8] & 0x0F) << 8) | data[9]),
      desc_list(),
      transport_stream_loop_length(((data[10 + network_descriptors_length] & 0x0F) << 8) | data[11 + network_descriptors_length]),
      streaminfo_list(),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    if(crc != 0xFFFFFFFF)
    {
        if(crc != crc32)
            throw new CrcErr(CrcErr::CNIT);
    }
}

//##ModelId=555828A60271
NIT::~NIT()
{
    std::list<TransStreamInfo*>::iterator tsit;
    for(tsit = streaminfo_list.begin(); tsit != streaminfo_list.end(); ++tsit)
    {
        delete (*tsit);
    }
    streaminfo_list.clear();

    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

NIT::TransStreamInfo::TransStreamInfo(uint8_t* data)
    : transport_stream_id((data[0] << 8) | data[1]),
      original_network_id((data[2] << 8) | data[3]),
      transport_descriptors_length(((data[4] & 0x0F) << 8) | data[5])
{
    int index = 0;
    uint8_t* sub_data = data + 6;
    DescFactory des_fac;
    while(index < transport_descriptors_length)
    {
        Descriptor* des = des_fac.createDesc(sub_data[index], sub_data + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }
}

//##ModelId=555D8D5B00B0
NIT::TransStreamInfo::~TransStreamInfo()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

bool NIT::joinTo(TSFactory* sf)
{
    std::pair<std::set<NIT*, cmp_secp<NIT>>::iterator, bool> ret;
    ret = sf->nit_list.insert(this);
    if(ret.second)
        this->getDetail();
    return ret.second;
}

void NIT::getDetail()
{
    if(raw_data == NULL)
        return ;

    int index = 0;
    uint8_t* sub_data = raw_data + 10;
    DescFactory des_fac;
    while(index < network_descriptors_length)
    {
        Descriptor* des = des_fac.createDesc(sub_data[index], sub_data + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }

    index = 0;
    sub_data = raw_data + 12 + network_descriptors_length;
    while(index < transport_stream_loop_length)
    {
        TransStreamInfo* tsi = new TransStreamInfo(sub_data + index);
        index += 6 + tsi->transport_descriptors_length;
        streaminfo_list.push_back(tsi);
    }

    delete []raw_data;
    raw_data = NULL;
}

bool NIT::operator ==(const NIT& nt)
{
    return table_id == nt.table_id &&
           network_id == nt.network_id &&
           version_number == nt.version_number &&
           section_number == nt.section_number;
           
    //return crc32 == nt.crc32;
}

bool NIT::operator<(const NIT& nt)
{
    if(table_id < nt.table_id)
        return true;
    else if(table_id == nt.table_id)
    {
        if(network_id < nt.network_id)
            return true;
        else if(network_id == nt.network_id)
        {
            if(version_number < nt.version_number)
                return true;
            else if(version_number == nt.version_number)
            {
                if(section_number < nt.section_number)
                    return true;
            }
        }
    }

    return false;
}

void NIT::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Section::resolved();
    xml->SetAttribute("table_id", table_id);
    xml->SetAttribute("network_id", network_id);
    xml->SetAttribute("version_number", version_number);
    xml->SetAttribute("section_number", section_number);

    sprintf(arr, "0x%x", network_id);
    tmp = new TiXmlElement("network_id");
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

    sprintf(arr, "0x%x", network_descriptors_length);
    tmp = new TiXmlElement("network_descriptors_length");
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

    sprintf(arr, "0x%x", transport_stream_loop_length);
    tmp = new TiXmlElement("transport_stream_loop_length");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    if(!streaminfo_list.empty())
    {
        std::list<TransStreamInfo*>::iterator tit;
        for(tit = streaminfo_list.begin(); tit != streaminfo_list.end(); ++tit)
        {
            tmp = new TiXmlElement("TransportStream");

            sprintf(arr, "0x%x", (*tit)->transport_stream_id);
            TiXmlElement* tms = new TiXmlElement("transport_stream_id");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*tit)->original_network_id);
            tms = new TiXmlElement("original_network_id");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*tit)->transport_descriptors_length);
            tms = new TiXmlElement("transport_descriptors_length");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);
            
            if(!(*tit)->desc_list.empty())
            {
                tms = new TiXmlElement("Descriptors");
                std::list<Descriptor*>::iterator sdit;
                for(sdit = (*tit)->desc_list.begin(); sdit != (*tit)->desc_list.end(); ++sdit)
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

