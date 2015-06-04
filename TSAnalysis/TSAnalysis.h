#ifndef _TS_ANALYSIS_H_
#define _TS_ANALYSIS_H_

#include "../Section/SectionFactory.h"

class PCR_Info
{
public:

    PCR_Info(uint16_t pid = 0xFFFF, uint32_t max_sz = 100);
    ~PCR_Info();

    void append(uint64_t pcr);

    long double MaxPCRInterval() {return max_pcr_interval;}
    long double MinPCRInterval() {return min_pcr_interval;}
    long double AvgPCRInterval() {return avg_pcr_interval;}

    /*long double MaxPCRJitter() {return max_pcr_jitter;}
    long double MinPCRJitter() {return min_pcr_jitter;}
    long double CurPCRJitter() {return cur_pcr_jitter;}*/

    uint32_t Number() {return number;}

    uint16_t PID;
    uint32_t max_size;
    // pkt number between two pcr
    uint32_t pkt_num;
    double one_pkt_interval;
private:
    uint32_t number;
    std::list<int64_t> pcr_list;
    std::list<double> itv_list;
    std::list<double> jit_list;
   
    // ms
    long double max_pcr_interval;
    long double min_pcr_interval;
    long double avg_pcr_interval;
    long double cur_pcr_interval;

    // ns
    long long max_pcr_jitter;
    long long min_pcr_jitter;
    long long cur_pcr_jitter;
};

class TSAnalysis
{
public:
    enum {TS_PACKET_SIZE = 188};
    enum {TS_DVHS_PACKET_SIZE = 192};
    enum {TS_FEC_PACKET_SIZE = 204};
    enum {TS_MAX_PACKET_SIZE = 204};

    TSAnalysis();
    TSAnalysis(char* infile);
    virtual ~TSAnalysis();

    void ts_analysis();
    int64_t get_pcr(const uint8_t *buf, int len);

private:
    int analyze(const uint8_t *buf, int size, int packet_size, int *index);
    int get_packet_size(const uint8_t *buf, int size, int* index);
    bool is_section_pkt(uint16_t pid);
    bool is_pcr_pkt(uint16_t pid);

    std::ifstream inf;
    char* in_ts_file;

    SectionFactory* sf;
    
    std::list<PCR_Info*> pcr_info_list;
};

#endif