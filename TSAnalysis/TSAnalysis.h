#ifndef _TS_ANALYSIS_H_
#define _TS_ANALYSIS_H_

#include "TSFactory.h"

struct TS_err
{
    TS_err() 
        : err(0), 
          level1_err(0), level2_err(0), level3_err(0), 
          sync_loss_err(0), sync_byte_err(0), 
          pat_err(0), pat_intv_err(0), pat_srb_err(0), pat_tid_err(0),
          cc_err(0),
          pmt_err(0), pmt_intv_err(0), pmt_srb_err(0),
          trans_err(0),
          crc_err(0), crc_bat_err(0), crc_pat_err(0), crc_pmt_err(0), crc_sdt_err(0), 
          crc_tot_err(0), crc_cat_err(0), crc_eit_err(0), crc_nit_err(0),
          pcr_intv_err(0), pcr_disc_err(0), pcr_acu_err(0),
          pts_err(0),
          cat_err(0), cat_srb_err(0), cat_tid_err(0),
          err_lmq()
    {

    }

    ~TS_err()
    {
        int sz = err_lmq.size();
        for(int i = 0; i < sz; ++i)
            delete err_lmq[i];
    }

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

    std::vector<TsErr*> err_lmq;
};


class TSAnalysis
{
public:
    TSAnalysis(char* infile);
    ~TSAnalysis();

    void ts_analysis();
    void save_es(int pid, char* es_file);
    //char* get_analysis_file();

    TS_err ts_err;
    TSFactory* sf;
    int pkt_sz;
    bool analyzing;

private:
    int analyze(const uint8_t *buf, int size, int packet_size, int *index); 
    int get_packet_size(const uint8_t *buf, int size, int* index); // get the packet size and find the start position

    int synchronous(SyncErr* se); //when sync_err occurs, this function to find the sync byte again
    void set_err_timepos(TsErr* te);

    FILE* inf;
    char in_ts_file[128];
};

#endif