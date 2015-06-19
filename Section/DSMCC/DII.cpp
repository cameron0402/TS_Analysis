#include "DII.h"

DII::Module::Module()
{

}

DII::Module::Module(uint8_t* data, uint16_t blk_sz)
    : moduleID((data[0] << 8) | data[1]),
      module_size((data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5]),
      module_version(data[6]),
      module_info_length(data[7]),
      block_size(blk_sz),
      block_sum(module_size / block_size + ((module_size % block_size) ? 1 : 0)),
      block_recv(0),
      recv_length(0),
      recv_completed(false),
      position(0),
      link_module_id(0),
      compressed(false),
      raw_module_size(module_size)
{
    int idx = 0;
    uint8_t* pd = data + 8;
    mdif = new ModuleInfo(pd);

    block_map = new uint8_t[block_sum];
    memset(block_map, 0, block_sum);

    module_data = new uint8_t[module_size];
}

bool DII::Module::operator<(const Module& md)
{
    return moduleID < md.moduleID;
}

bool DII::Module::operator==(const Module& md)
{
    return moduleID == md.moduleID;
}

DII::Module::~Module()
{
    if(mdif != NULL)
        delete mdif;
    if(block_map != NULL)
        delete []block_map;
    if(module_data != NULL)
        delete []module_data;
}

bool DII::Module::check_recv_completed()
{
    if(!recv_completed)
    {
        if(recv_length == module_size &&
           block_recv == block_sum)
        {
           recv_completed = true;
        }
    }
    return recv_completed;
}

DII::ModuleInfo::Tap::Tap()
{

}

DII::ModuleInfo::Tap::Tap(uint8_t* data)
    : ID((data[0] << 8) | data[1]),
      use((data[2] << 8) | data[3]),
      association_tag((data[4] << 8) | data[5]),
      selector_length(data[6])
{

}

DII::ModuleInfo::Tap::~Tap()
{

}

DII::ModuleInfo::ModuleInfo()
{

}

DII::ModuleInfo::ModuleInfo(uint8_t* data)
    : module_time_out((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]),
      block_time_out((data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]),
      min_block_time((data[8] << 24) | (data[9] << 16) | (data[10] << 8) | data[11]),
      taps_count(data[12])
{
    uint8_t* pd = data + 13;
    int idx = 0;
    int i = 0;
    for(i = 0; i < taps_count; ++i)
    {
        DII::ModuleInfo::Tap* ti = new DII::ModuleInfo::Tap(pd + idx);
        tap_list.push_back(ti);
        idx += 7;
    }

    pd += idx;
    desc_length = pd[idx];
    DSMCCDescFactory desfac;
    idx = 0;
    while(idx < desc_length)
    {
        Descriptor* des = desfac.createDesc(pd[idx], pd + idx);
        dsmcc_desc_list.push_back(des);
        idx += des->length + 2;
    }
}

DII::ModuleInfo::~ModuleInfo()
{
    std::list<DII::ModuleInfo::Tap*>::iterator tit;
    for(tit = tap_list.begin(); tit != tap_list.end(); ++tit)
        delete (*tit);

    std::list<Descriptor*>::iterator dit;
    for(dit = dsmcc_desc_list.begin(); dit != dsmcc_desc_list.end(); ++dit)
        delete (*dit);
}

DII::DII()
{

}

DII::DII(uint8_t* data)
{
   dsmh = new DsmccMessageHeader(data);
   uint8_t* pd = data + 12 + dsmh->adaptation_length;
   downloadID = (pd[0] << 24) | (pd[1] << 16) | (pd[2] << 8) | (pd[3]);
   block_size = (pd[4] << 8) | pd[5];
   window_size = pd[6];
   ack_period = pd[7];
   tc_download_window = (pd[8] << 24) | (pd[9] << 16) | (pd[10] << 8) | pd[11];
   tc_download_scenario = (pd[12] << 24) | (pd[13] << 16) | (pd[14] << 8) | pd[15];
   compatibility = (pd[16] << 8) | pd[17];
   module_number = (pd[18] << 8) | pd[19];

   int idx = 0;
   int i;
   pd += 20;
   for(i = 0; i < module_number; ++i)
   {
       DII::Module* md = new DII::Module(pd + idx, block_size);
       mod_list.insert(md);
       idx += md->module_info_length + 8;
   }

   private_data_length = (pd[idx] << 8) | pd[idx + 1];
   std::set<DII::Module*, cmp_secp<Module>>::iterator mit;
   for(mit = mod_list.begin(); mit != mod_list.end(); ++mit)
   {
       check_sum += (*mit)->block_size;
   }
}

DII::~DII()
{
    std::set<DII::Module*, cmp_secp<Module>>::iterator mit;
    for(mit = mod_list.begin(); mit != mod_list.end(); ++mit)
        delete (*mit);
}