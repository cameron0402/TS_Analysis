#include "TSAnalysis.h"
#include "../Section/PAT.h"

TSAnalysis::TSAnalysis()
{

}

TSAnalysis::TSAnalysis(char* infile)
    : in_ts_file(infile),
      inf(infile, std::ifstream::binary)
{
}


TSAnalysis::~TSAnalysis()
{
    inf.close();
}

int TSAnalysis::analyze(const uint8_t* buf, int size, int packet_size, int* index)
{
    int stat[TS_MAX_PACKET_SIZE];
    int i;
    int best_score = 0;

    memset(stat, 0, packet_size * sizeof(*stat));

    for(i = 0; i < size - 3; i++)
    {
        if(buf[i] == 0x47 && !(buf[i+1] & 0x80) && buf[i+3] != 0x47)
        {
            int x = i % packet_size;
            stat[x]++;
            if(stat[x] > best_score)
            {
                best_score = stat[x];
                if(index) 
                    *index = x;
            }
        }
    }

    return best_score;
}

/* autodetect fec presence. Must have at least 1024 bytes  */
int TSAnalysis::get_packet_size(const uint8_t* buf, int size, int* index = NULL)
{
    int score, fec_score, dvhs_score;
    int idx, fec_idx, dvhs_idx;
    if (size < (TS_FEC_PACKET_SIZE * 5 + 1))
        return -1;

    score = analyze(buf, size, TS_PACKET_SIZE, &idx);
    dvhs_score = analyze(buf, size, TS_DVHS_PACKET_SIZE, &fec_idx);
    fec_score = analyze(buf, size, TS_FEC_PACKET_SIZE, &dvhs_idx);

    if(score > fec_score && score > dvhs_score) 
    {
        if(index != NULL)
            *index = idx;
        return TS_PACKET_SIZE;
    }
    else if(dvhs_score > score && dvhs_score > fec_score) 
    {
        if(index != NULL)
            *index = dvhs_idx;
        return TS_DVHS_PACKET_SIZE;
    }
    else if(fec_score > score && fec_score > dvhs_score) 
    {
        if(index != NULL)
            *index = fec_idx;
        return TS_FEC_PACKET_SIZE;
    }

    return -1;
}

bool TSAnalysis::is_section_pkt(uint16_t type)
{
    if(type == 0x00 /*||
       type == 0x01 ||
       type == 0x10 ||
       type == 0x11 ||
       type == 0x12 ||
       type == 0x14*/)
    {
        return true;
    }

    if(sf->pat != NULL)
    {
        std::list<PAT::ProgInfo*>::iterator pit;
        for(pit = sf->pat->prog_list.begin(); pit != sf->pat->prog_list.end(); pit++)
        {
            if(type == (*pit)->program_map_PID)
                return true;
        }
    }

    return false;
    
}

void TSAnalysis::ts_analysis()
{
    uint8_t test_buf[TS_MAX_PACKET_SIZE * 6] = {0};
    inf.read((char*)test_buf, TS_MAX_PACKET_SIZE * 6);

    int st_idx = 0;
    int pkt_sz = 0;
    pkt_sz = get_packet_size(test_buf, TS_MAX_PACKET_SIZE * 6, &st_idx);
    if(pkt_sz == -1)
    {
        std::cout << "could not analysis the TS!\n";
        return ;
    }

    inf.seekg(st_idx, inf.beg);
    sf = SectionFactory::GetInstance();
    while(!inf.eof())
    {
        inf.read((char*)test_buf, pkt_sz);
        uint16_t pid = ((test_buf[1] & 0x1F) << 8) | test_buf[2];
        if(is_section_pkt(pid))
            sf->sectionGather(test_buf);

        pid--;
    }
}