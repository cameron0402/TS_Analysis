#include "DsmccSection.h"

class module_finder
{
public:
    module_finder(uint16_t md_id) : module_id(md_id){}
    bool operator()(DII::Module* md)
    {
        return md->moduleID == module_id;
    }
private:
    uint16_t module_id;
};

DsmccSection::DsmccSection()
{

}

DsmccSection::DsmccSection(uint8_t* data, uint16_t len, uint32_t crc /* = 0xFFFFFFFF */)
    : Section(data, len, crc),
      table_id_extension((data[3] << 8) | data[4]),
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      crc((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1]),
      belong(NULL)
{
    dsmcc_data = new uint8_t[len - 12];
    memcpy(dsmcc_data, data + 8, len - 12);
}

DsmccSection::~DsmccSection()
{
    if(dsmcc_data)
        delete []dsmcc_data;
}

void DsmccSection::resolved()
{

}

void DsmccSection::setBelong(ESGInfo* bl)
{
    belong = bl;
}

bool DsmccSection::joinTo(SectionFactory* sf)
{
    if(belong != NULL)
        belong->saveDsmccData(this);
    return false;
}

ESGInfo::ESGInfo(uint16_t ser_id)
    : service_id(ser_id),
      pid_list(),
      dsi(NULL),
      dii_list()
{

}

ESGInfo::~ESGInfo()
{

}

void ESGInfo::saveDsmccData(DsmccSection* dss)
{
    uint16_t message_id;
    message_id = (dss->dsmcc_data[2] << 8) | dss->dsmcc_data[3];
    if(dss->table_id == 0x3B)
    {
        if(message_id == 0x1006) //dsi
        {
           saveDSIInfo(dss);
        }
        else if(message_id == 0x1002) //dii
        {
            saveDIIInfo(dss);
        }
        else
        {
            std::cout << "unknown message id...\n";
        }
    }
    else if(dss->table_id == 0x3C)
    {
        if(0x1003 != message_id)
        {
            std::cout << "unknown message id...\n";
        }
        else
        {
            saveDDBData(dss);
        }
    }
    else
    {
        std::cout << "unknown table id...\n";
    }
}

void ESGInfo::saveDSIInfo(DsmccSection* dss)
{
    if(dsi == NULL)
    {
        dsi = new DSI(dss->dsmcc_data);
    } 
}


void ESGInfo::saveDIIInfo(DsmccSection* dss)
{
    bool update = false;
    DII* dii = new DII(dss->dsmcc_data);
    std::list<DII*>::iterator dit;
    for(dit = dii_list.begin(); dit != dii_list.end(); ++dit)
    {
        if((*dii) == *(*dit))
        {
            delete dii;
            dii = NULL;
            break;
        }
        else
        {
            if(dii->dsmh->transactionId == (*dit)->dsmh->transactionId &&
                dii->check_sum != (*dit)->check_sum)
            {
                update = true;
                break;
            }
        }
    }

    if(update)
    {
        reset();
    }

    if(dii != NULL)
        dii_list.push_back(dii);
}

void ESGInfo::saveDDBData(DsmccSection* dss)
{
    uint8_t adp_len = dss->dsmcc_data[9];
    uint16_t data_len = (dss->dsmcc_data[10] << 8) | dss->dsmcc_data[11];

    uint8_t* pd = dss->dsmcc_data + 12 + adp_len;

    data_len -= adp_len;
    uint16_t md_id = (pd[0] << 8) | pd[1];
    uint16_t blk_num = (pd[4] << 8) | pd[5];

    pd += 6;
    data_len -= 6;

    bool find = false;
    std::set<DII::Module*, cmp_secp<DII::Module>>::iterator fit;
    std::list<DII*>::iterator dit;
    for(dit = dii_list.begin(); dit != dii_list.end(); ++dit)
    {
        if((fit = std::find_if((*dit)->mod_list.begin(), (*dit)->mod_list.end(), module_finder(md_id))) != (*dit)->mod_list.end())
        {
            find = true;
            break;
        }
    }

    if(find)
    {
        if((*fit)->recv_completed)
            return ;
        else
        {
            if((*fit)->block_map[blk_num] == 0xFF)
                return ;
            else
            {
                if((*fit)->block_size * blk_num + data_len > (*fit)->module_size)
                {
                    std::cout << "module size is too big! maybe the dii info has updated...\n";
                    return;
                }
                memcpy((*fit)->module_data + (*fit)->block_size * blk_num, pd, data_len);
                (*fit)->block_map[blk_num] = 0xFF;
                (*fit)->recv_length += data_len;
                if((*fit)->recv_length == (*fit)->module_size)
                {
                    (*fit)->recv_completed = true;
                    (*fit)->resolved();
                }
            }
        }
    }
}

void ESGInfo::reset()
{
    if(dsi != NULL)
    {
        delete dsi;
        dsi = NULL;
    }

    std::list<DII*>::iterator dit;
    for(dit = dii_list.begin(); dit != dii_list.end(); ++dit)
    {
        delete (*dit);
    }
    dii_list.clear();
}

