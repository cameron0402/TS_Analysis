#include "TSAnalysis.h"
#include "../Section/PAT.h"
#include "../Section/PMT.h"

PCR_Info::PCR_Info(uint16_t pid, uint32_t max_sz)
    : PID(pid),
      max_size(max_sz),
      pkt_num(0),
      one_pkt_interval(0),
      number(0),
      pcr_list(0),
      itv_list(0),
      jit_list(0),
      max_pcr_interval(0),
      min_pcr_interval(1000),
      avg_pcr_interval(0),
      cur_pcr_interval(0),
      max_pcr_jitter(-1000),
      min_pcr_jitter(1000),
      cur_pcr_jitter(0)
{
}

PCR_Info::~PCR_Info()
{

}

void PCR_Info::append(uint64_t pcr)
{
    static uint32_t last_pkt_num = 0;
    static long long last_intv = 0;

    uint64_t tp = 0;
    if(!pcr_list.empty())
        tp = pcr_list.back();

    if(pcr_list.size() > max_size)
    {
        pcr_list.pop_front();
    }
    pcr_list.push_back(pcr);

    ++number;

    if(tp != 0)
    {
        long double pcr_intv = (long double)(pcr - tp) / 27000.0;
        if(pcr_intv > max_pcr_interval) max_pcr_interval = pcr_intv;
        if(pcr_intv < min_pcr_interval) min_pcr_interval = pcr_intv;
        avg_pcr_interval = (avg_pcr_interval * (number - 1) + pcr_intv) / number;
        if(itv_list.size() > max_size)
        {
            itv_list.pop_front();
        }
        itv_list.push_back(pcr_intv);
        
        if(cur_pcr_interval != 0)
        {
            long long expect_pcr_intv;
            long long pcr_jitter;
            expect_pcr_intv = last_intv * (pkt_num - 1) / (last_pkt_num - 1);
            pcr_jitter = (pcr - tp) - expect_pcr_intv;
            if(pcr_jitter > max_pcr_jitter) max_pcr_jitter = pcr_jitter;
            if(pcr_jitter < min_pcr_jitter) min_pcr_jitter = pcr_jitter;
            cur_pcr_jitter = pcr_jitter;
            if(jit_list.size() > max_size)
            {
                jit_list.pop_front();
            }
            jit_list.push_back(cur_pcr_jitter);
        }

        cur_pcr_interval = pcr_intv;
    }
    last_intv = pcr - tp;
    last_pkt_num = pkt_num;
    pkt_num = 0;
}

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

bool TSAnalysis::is_section_pkt(uint16_t pid)
{
    if(/*pid == 0x00  ||
       pid == 0x01 ||*/
       pid == 0x10 ||
       pid == 0x11 ||
       pid == 0x12 ||
       pid == 0x14)
    {
        return true;
    }

    /*if(sf->pat != NULL)
    {
        std::list<PAT::ProgInfo*>::iterator pit;
        for(pit = sf->pat->prog_list.begin(); pit != sf->pat->prog_list.end(); pit++)
        {
            if(pid == (*pit)->program_map_PID)
                return true;
        }
    }*/

    return false;
    
}

bool TSAnalysis::is_pcr_pkt(uint16_t pid)
{
    if(!sf->pmt_list.empty())
    {
        std::list<PMT*>::iterator pit;
        for(pit = sf->pmt_list.begin(); pit != sf->pmt_list.end(); ++pit)
        {
            if(pid == (*pit)->PCR_PID)
                return true;
        }
    }
    return false;
}

int64_t TSAnalysis::get_pcr(const uint8_t *buf, int len)
{
    if(!((buf[3] >> 5) & 0x1))
    {
        //std::cout << "No adaptation field." << std::endl;
        return -1;
    }

    const uint8_t* adp = buf + 4;
    if(adp[0] == 0)
    {
        //std::cout << "Adaptation field length is zero." << std::endl;
        return -1;
    }

    if(!((adp[1] >> 4) & 0x1))
    {
        //std::cout << "PCR flag is not set." << std::endl;
        return -1;
    }

    int64_t pcr_base = ((int64_t)adp[2] << 25) | (adp[3] << 17) | (adp[4] << 9) | (adp[5] << 1) | (adp[6] >> 7);
    int64_t pcr_ext = ((adp[7] & 0x1) << 8) | adp[8];

    return pcr_base * 300 + pcr_ext;
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

       /* std::list<PCR_Info*>::iterator pit;
        for(pit = pcr_info_list.begin(); pit != pcr_info_list.end(); ++pit)
        {
            (*pit)->pkt_num++;
        }
*/
        if(pid == 0x1FFF) //empty packet
            continue;

        if(is_section_pkt(pid))
        {
            sf->sectionGather(pid, test_buf);
        }

        /*if(is_pcr_pkt(pid))
        {
        int64_t pcr = get_pcr(test_buf, pkt_sz);
        if(pcr == -1)
        continue;
        std::list<PCR_Info*>::iterator pit;
        bool ex = false;
        for(pit = pcr_info_list.begin(); pit != pcr_info_list.end(); ++pit)
        {
        if((*pit)->PID == pid)
        {
        (*pit)->append(pcr);
        ex = true;
        break;
        }
        }

        if(!ex)
        {
        PCR_Info* pi = new PCR_Info(pid);
        pi->append(pcr);
        pcr_info_list.push_back(pi);
        }
        }*/
    }
}