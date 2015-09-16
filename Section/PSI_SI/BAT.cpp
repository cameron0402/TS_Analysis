#include "BAT.h"
#include "../../TSAnalysis/TSFactory.h"
#include "../../Descriptor/Descriptor.h"
#include "../../Descriptor/DVB/DescFactory.h"

//##ModelId=55628F4000F1
BAT::TransStreamInfo::TransStreamInfo()
{
}

//##ModelId=55628F4C0029
BAT::TransStreamInfo::TransStreamInfo(uint8_t* data)
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

BAT::TransStreamInfo::~TransStreamInfo()
{
    std::list<Descriptor*>::iterator dit;
    for(dit = desc_list.begin(); dit != desc_list.end(); ++dit)
    {
        delete (*dit);
    }
    desc_list.clear();
}

BAT::BAT(uint8_t* data, uint16_t len, uint32_t crc)
    : Section(data, len),
      bouquet_id((data[3] << 8) | data[4]), 
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      bouquet_descriptors_length(((data[8] & 0x0F) << 8) | data[9]),
      desc_list(),
      transport_stream_loop_length(((data[10 + bouquet_descriptors_length] & 0x0F) << 8) | data[11 + bouquet_descriptors_length]),
      streaminfo_list(),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    if(crc != 0xFFFFFFFF)
    {
        if(crc != crc32)
            throw new CrcErr(CrcErr::CBAT);
    }
}

BAT::~BAT()
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

bool BAT::operator==(const BAT& bt)
{
    return bouquet_id == bt.bouquet_id &&
           section_number == bt.section_number;
}

bool BAT::operator<(const BAT& bt)
{
    if(bouquet_id < bt.bouquet_id)
        return true;
    else if(bouquet_id == bt.bouquet_id)
    {
        if(section_number < bt.section_number)
            return true;
    }
    return false;
}

bool BAT::joinTo(TSFactory* sf)
{
    std::pair<std::set<BAT*, cmp_secp<BAT>>::iterator, bool> ret
        = sf->bat_list.insert(this);
    if(ret.second)
    {
        this->getDetail();
    }
    return ret.second;
}

void BAT::getDetail()
{
    if(raw_data == NULL)
        return ;

    int index = 0;
    uint8_t* sub_data = raw_data + 10;
    DescFactory des_fac;
    while(index < bouquet_descriptors_length)
    {
        Descriptor* des = des_fac.createDesc(sub_data[index], sub_data + index);
        index += des->length + 2;
        desc_list.push_back(des);
    }

    index = 0;
    sub_data = raw_data + 12 + bouquet_descriptors_length;
    while(index < transport_stream_loop_length)
    {
        TransStreamInfo* tsi = new TransStreamInfo(sub_data + index);
        index += 6 + tsi->transport_descriptors_length;
        streaminfo_list.push_back(tsi);
    }

    delete []raw_data;
    raw_data = NULL;
}

