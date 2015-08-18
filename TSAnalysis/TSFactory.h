#ifndef _TS_FACTORY_H_
#define _TS_FACTORY_H_

#include "../def.h"
#include "TSData.h"
#include "../Descriptor/DVB/DescFactory.h"
#include "../Section/Section.h"
#include "../Section/PSI_SI/BAT.h"
#include "../Section/PSI_SI/CAT.h"
#include "../Section/PSI_SI/EIT.h"
#include "../Section/PSI_SI/NIT.h"
#include "../Section/PSI_SI/PAT.h"
#include "../Section/PSI_SI/PMT.h"
#include "../Section/PSI_SI/SDT.h"
#include "../Section/PSI_SI/TDT.h"
#include "../Section/PSI_SI/TOT.h"
#include "../Section/DSMCC/DsmccSection.h"   

class Stream
{
public:
    Stream(PMT::StreamInfo* si);
    ~Stream();

    const struct stream_type_table* stream_type;
    uint16_t stream_pid;
    bool scrambling;

    LimitQueue<int64_t> pts_list;
    LimitQueue<int64_t> dts_list;
};

class ProgInfo
{
public:
    ProgInfo(uint8_t* data);
    virtual ~ProgInfo();

    void setInfo(PMT* pmt);

    uint16_t program_number;
    uint16_t program_map_PID;

    uint16_t pcr_pid;
    bool scrambling;

    LimitQueue<int64_t> pcr_list;
    LimitQueue<uint32_t> pcr_pkt_list; 
    std::list<Stream*> stream_list;
};

class TSFactory
{
public:
    ~TSFactory();
    bool addSection(Section* section);
    virtual Section* createSectoin(TSData* raw_section);
    static TSFactory* GetInstance();
    void TSGather(int pid, uint8_t* ts_packet);
    void ESGather(int pid, uint8_t* ts_packet, std::ofstream& of);
    
    PAT* pat;
    std::set<PMT*, cmp_secp<PMT>> pmt_list;
    std::set<NIT*, cmp_secp<NIT>> nit_list;
    std::set<CAT*, cmp_secp<CAT>> cat_list;
    std::set<BAT*, cmp_secp<BAT>> bat_list;
    std::set<SDT*, cmp_secp<SDT>> sdt_list;
    std::set<EIT*, cmp_secp<EIT>> eit_list;
    TDT* tdt;
    TOT* tot;
    std::list<ESGInfo*> esg_list; 
    std::list<ESGInfo*> esg_stable_list;

    TSData* raw_sarr[MAX_PID_NUM];
    std::vector<uint16_t> pid_vec;

    uint16_t pcr_pid; //stream of all pids use this pcr_pid
    uint32_t pkt_num;
    double max_bit_rate;
    double min_bit_rate;
    double cur_bit_rate;

    TSData* createTSdata(uint16_t pid);
    TSData* createTSdata(uint16_t pid, int type, char* sdes);

private:
    TSFactory();
    TSFactory(const TSFactory&);
    TSFactory& operator=(const TSFactory&);

    int adaptationFieldAnalysis(uint8_t* ts_packet, TSData* raw_ts,
                                bool& pcr_inv_err, bool& pcr_dis_err, bool& pcr_acu_err);
    bool continuityCheck(uint8_t* ts_packet, TSData* raw_ts, bool& cc_err);
    void SectionAnalysis(TSData* raw_ts);
    void PESAnalysis(TSData* raw_ts);

    static TSFactory* _instance;
};



#endif 
