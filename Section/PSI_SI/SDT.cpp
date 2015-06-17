#include "SDT.h"
#include "../SectionFactory.h"
#include "../../Descriptor/Descriptor.h"
#include "../../Descriptor/DVB/DescFactory.h"

//##ModelId=5563CDBD00BF
SDT::SDT()
{
}

//##ModelId=5563CDCB02BF
SDT::SDT(uint8_t* data, uint16_t len, uint32_t crc)
    : Section(data, len),
      transport_stream_id((data[3] << 8) | data[4]), 
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      original_network_id((data[8] << 8) | data[9]),
      service_list(),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    if(crc != 0xFFFFFFFF)
    {
        if(crc != crc32)
            throw CrcErr(CrcErr::CSDT);
    }
}

//##ModelId=5563CE0800BB
SDT::~SDT()
{
    std::list<ServiceInfo*>::iterator sit;
    for(sit = service_list.begin(); sit != service_list.end(); ++sit)
    {
        delete (*sit);
    }
    service_list.clear();
}

//##ModelId=5563D0B20194
SDT::ServiceInfo::ServiceInfo()
{
}

//##ModelId=5563D0B900DD
SDT::ServiceInfo::ServiceInfo(uint8_t* data)
    : service_id((data[0] << 8) | data[1]),
      EIT_schedule_flag((data[2] >> 1) & 0x01),
      EIT_present_following_flag(data[2] & 0x01),
      running_status(data[3] >> 5),
      free_CA_mode((data[3] >> 4) & 0x01),
      descriptors_loop_length(((data[3] & 0x0F) << 8) | data[4])
{
    int idx = 0;
    DescFactory des_fac;
    uint8_t* pd = data + 5;
    while(idx < descriptors_loop_length)
    {
        Descriptor* des = des_fac.createDesc(pd[idx], pd + idx);
        desc_list.push_back(des);
        idx += des->length + 2;
    }
}

//##ModelId=5563D0D1019A
SDT::ServiceInfo::~ServiceInfo()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

bool SDT::operator==(const SDT& st)
{
    return table_id == st.table_id &&
           original_network_id == st.original_network_id &&
           transport_stream_id == st.transport_stream_id &&
           version_number == st.version_number &&
           section_number == st.section_number;
    //return crc32 == st.crc32;
}

bool SDT::operator<(const SDT& st)
{
    if(table_id < st.table_id)
        return true;
    else if(table_id == st.table_id)
    {
        if(original_network_id < st.original_network_id)
            return true;
        else if(original_network_id == st.original_network_id)
        {
            if(transport_stream_id < st.transport_stream_id)
                return true;
            else if(transport_stream_id == st.transport_stream_id)
            {
                if(version_number < st.version_number)
                    return true;
                else if(version_number == st.version_number)
                {
                    if(section_number < st.section_number)
                        return true;
                }
            }
        }
    }
    return false;
}

bool SDT::joinTo(SectionFactory* sf)
{
    std::pair<std::set<SDT*, cmp_secp<SDT>>::iterator, bool> ret;
    ret = sf->sdt_list.insert(this);
    return ret.second;
}

void SDT::getDetail(uint8_t* data, uint16_t len)
{
    int index = 11;
    while(index < len - 4)
    {
        ServiceInfo* si = new ServiceInfo(data + index);
        service_list.push_back(si);
        index += 5 + si->descriptors_loop_length;
    }
}

void SDT::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Section::resolved();
    xml->SetAttribute("table_id", table_id);
    xml->SetAttribute("original_network_id", original_network_id);
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

    sprintf(arr, "0x%x", original_network_id);
    tmp = new TiXmlElement("original_network_id");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    

    if(!service_list.empty())
    {
        std::list<ServiceInfo*>::iterator sit;
        for(sit = service_list.begin(); sit != service_list.end(); ++sit)
        {
            tmp = new TiXmlElement("Service");

            sprintf(arr, "0x%x", (*sit)->service_id);
            TiXmlElement* tms = new TiXmlElement("service_id");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*sit)->EIT_schedule_flag);
            tms = new TiXmlElement("EIT_schedule_flag");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*sit)->EIT_present_following_flag);
            tms = new TiXmlElement("EIT_present_following_flag");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*sit)->running_status);
            tms = new TiXmlElement("running_status");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*sit)->free_CA_mode);
            tms = new TiXmlElement("free_CA_mode");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            sprintf(arr, "0x%x", (*sit)->descriptors_loop_length);
            tms = new TiXmlElement("descriptors_loop_length");
            tms->LinkEndChild(new TiXmlText(arr));
            tmp->LinkEndChild(tms);

            if(!(*sit)->desc_list.empty())
            {
                tms = new TiXmlElement("Descriptors");
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

