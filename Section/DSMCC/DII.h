#ifndef _DII_H_
#define _DII_H_

#include "DsmccMessageHeader.h"
#include "ObjDsmcc.h"
#include "../../Descriptor/Descriptor.h"
#include "../../Descriptor/DSMCC/DSMCCDescFactory.h"

class DII
{
public:
    class ModuleInfo
    {
    public:
        class Tap
        {
        public:
            Tap();
            Tap(uint8_t* data);
            ~Tap();

            uint16_t ID;
            uint16_t use; //0x0017 BIOP_OBJECT_USE
            uint16_t association_tag;
            uint8_t selector_length;
        };
        ModuleInfo();
        ModuleInfo(uint8_t* data);
        ~ModuleInfo();

        uint32_t module_time_out;
        uint32_t block_time_out;
        uint32_t min_block_time;
        uint8_t taps_count;
        std::list<Tap*> tap_list;
        uint8_t desc_length;
        std::list<Descriptor*> dsmcc_desc_list;
    };

    class Module
    {
    public:
        Module();
        Module(uint8_t* data, uint16_t blk_sz);
        virtual ~Module();
        void resolved();
        bool operator <(const Module& md);
        bool operator ==(const Module& md);

        uint16_t moduleID;
        uint32_t module_size;
        uint8_t module_version;
        uint8_t module_info_length;
        ModuleInfo* mdif;

        uint16_t block_size;
        uint16_t block_sum;
        uint8_t* block_map;

        uint32_t recv_length;
        bool recv_completed;

        uint8_t position;
        uint16_t link_module_id;

        bool compressed;
        uint32_t raw_module_size;   

        uint8_t* module_data;

        std::set<ObjDsmcc*, cmp_secp<ObjDsmcc>> obj_list;
    };

    DII();
    DII(uint8_t* data);
    virtual ~DII();

    bool operator<(const DII& dii);
    bool operator==(const DII& dii);

    DsmccMessageHeader* dsmh;
    uint32_t downloadID;
    uint16_t block_size;
    uint8_t window_size;
    uint8_t ack_period;
    uint32_t tc_download_window;
    uint32_t tc_download_scenario;
    uint16_t compatibility;
    uint16_t module_number;  
    std::set<Module*, cmp_secp<Module>> mod_list;
    uint16_t private_data_length;

    uint32_t check_sum;
    //uint8_t* private_data;
};

#endif