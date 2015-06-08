#ifndef _TS_ANALYSIS_H_
#define _TS_ANALYSIS_H_

#include "../Section/SectionFactory.h"

enum PID_type {PNUL, SECTION, ELE_STREAM};

struct TS_err
{
    int err;

    int level1_err;
    int level2_err;
    int level3_err;

    /* First priority: necessary for de-codability (basic monitoring) */
    int sync_loss_err;
    int sync_byte_err;
};


class TSAnalysis
{
public:

    struct PID_state
    {
        PID_type type;
        char* description;
        bool scrambling_flag;
        float avg_bitrate;
        float ratio;
        uint32_t pkt_num;
        uint32_t cc_err_num;
    };

    TSAnalysis();
    TSAnalysis(char* infile);
    virtual ~TSAnalysis();

    void ts_analysis();
    TS_err ts_err;
    TiXmlElement* err_xml;

private:
    int analyze(const uint8_t *buf, int size, int packet_size, int *index); 
    int get_packet_size(const uint8_t *buf, int size, int* index); // get the packet size and find the start position
    bool is_section_pkt(uint16_t pid);

    int synchronous(int pkt_sz); //when sync_err occurs, this function to find the sync byte again

    PID_state ps[MAX_PID_NUM];
    bool pmt_set;

    std::ifstream inf;
    char* in_ts_file;

    SectionFactory* sf;
};

#endif