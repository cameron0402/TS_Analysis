#ifndef _TS_ANALYSIS_H_
#define _TS_ANALYSIS_H_

#include "TSFactory.h"

struct TS_err
{
    int err;

    int level1_err;
    int level2_err;
    int level3_err;

    /* First priority: necessary for de-codability (basic monitoring) */
    // sync error
    int sync_loss_err;
    int sync_byte_err;

    //pat error
    int pat_err;
    int pat_intv_err; // interval > 500ms
    int pat_tid_err; // table_id != 0
    int pat_srb_err; // scrambling flag != 00

    // CC error
    int cc_err; // continuity count error

    //pmt error
    int pmt_err;
    int pmt_intv_err; // interval > 500ms
    int pmt_srb_err; // scrambling flag != 00

    /* Second priority: recommended for continuous or periodic monitoring */
    int trans_err; //transport_error_indicator == 1;

    // CRC error
    int crc_err;
    int crc_pat_err;
    int crc_pmt_err;
    int crc_cat_err;
    int crc_nit_err;
    int crc_eit_err;
    int crc_bat_err;
    int crc_sdt_err;
    int crc_tot_err;

    // PCR error
    int pcr_intv_err; // interval > 40ms
    int pcr_disc_err; // discontinuity_indicator == 0 && interval > 100ms
    int pcr_acu_err; // pcr jitter > 500ns || pcr jitter < -500ns

    int pts_err; // interval > 700ms
    
    // CAT error
    int cat_err;
    int cat_srb_err; // scrambling flag == 1 but have no cat 
    int cat_tid_err; // table_id != 0x01
};


class TSAnalysis
{
public:

    struct PID_state
    {
        //PID_type type;
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
    //bool is_section_pkt(uint16_t pid);

    int synchronous(int pkt_sz); //when sync_err occurs, this function to find the sync byte again

    PID_state ps[MAX_PID_NUM];
    bool pmt_set;

    std::ifstream inf;
    char* in_ts_file;

    TSFactory* sf;
};

#endif