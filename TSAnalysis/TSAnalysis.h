#ifndef _TS_ANALYSIS_H_
#define _TS_ANALYSIS_H_

#include "../Section/SectionFactory.h"

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

private:
    int analyze(const uint8_t *buf, int size, int packet_size, int *index);
    int get_packet_size(const uint8_t *buf, int size, int* index);
    bool is_section_pkt(uint16_t type);

    SectionFactory* sf;
    std::ifstream inf;
    char* in_ts_file;
};

#endif