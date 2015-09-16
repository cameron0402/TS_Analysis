#include "TSAnalysis.h"
#include "../Section/PSI_SI/PAT.h"
#include "../Section/PSI_SI/PMT.h"

TSAnalysis::TSAnalysis(char* infile)
    : ts_err(),
      sf(NULL),
      in_ts_file(),
      inf(NULL),
      pkt_sz(0),
      st_idx(-1),
      analyzing(false)
{
    //inf = fopen(infile, "rb");
    strcpy(in_ts_file, infile);
}


TSAnalysis::~TSAnalysis()
{
    if(sf != NULL)
    {
        delete sf;
        sf = NULL;
    }

    if(inf != NULL)
        fclose(inf);
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

void TSAnalysis::set_err_timepos(TsErr* te)
{
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    te->time = asctime(timeinfo);

    char tmp[128] = {0};
    sprintf(tmp, "第0x%x字节， 第0x%x包", ftell(inf), sf->pkt_num);
    te->pos = tmp;
}

int TSAnalysis::synchronous(SyncErr* se)
{
    int idx = 0;
    char buf[TS_MAX_PACKET_SIZE * 6] = {0};
    //inf.seekg(-pkt_sz, inf.cur);
    fseek(inf, -pkt_sz, SEEK_CUR);

    //inf.read(buf, TS_MAX_PACKET_SIZE * 6);
    fread(buf, TS_MAX_PACKET_SIZE * 6, 1, inf);

    while(idx < pkt_sz * 3)
    {
        if(buf[idx] == 0x47)
        {
            if(buf[idx + pkt_sz] == 0x47 &&
               buf[idx + pkt_sz * 2] == 0x47)
            {
                if(idx == pkt_sz)
                {
                    ++ts_err.sync_byte_err;
                    se->des_idx = 1;
                }
                else
                {
                    ++ts_err.sync_loss_err;
                    se->des_idx = 0;
                }
                ts_err.err_lmq.push_back(se);
                //inf.seekg(idx - TS_MAX_PACKET_SIZE * 6, inf.cur);
                fseek(inf, idx - TS_MAX_PACKET_SIZE * 6, SEEK_CUR);

                return idx;
            }
        }
        ++idx;
    }

    return -1;
}

//char* TSAnalysis::get_analysis_file()
//{
//    return in_ts_file;
//}

void TSAnalysis::save_es(int pid, char* es_file)
{
    uint16_t tpid;
    uint8_t test_buf[TS_MAX_PACKET_SIZE * 6] = {0};
    /*if(inf == NULL)
    return ;
    clearerr(inf);
    fseek(inf, 0, SEEK_SET);*/
    inf = fopen(in_ts_file, "rb");
    fread((char*)test_buf, TS_MAX_PACKET_SIZE * 6, 1, inf);
   
    int st_idx = 0;
    int pkt_sz = 0;
    pkt_sz = get_packet_size(test_buf, TS_MAX_PACKET_SIZE * 6, &st_idx);
    if(pkt_sz == -1)
    {
        std::cout << "can't find the sync-byte and can't analysis the TS!\n";
        return ;
    }
    fseek(inf, st_idx, SEEK_SET);

    FILE* of = fopen(es_file, "wb");
    if(of == NULL)
        return ;

    sf = TSFactory::GetInstance();
    while(!feof(inf))
    {
        //inf.read((char*)test_buf, pkt_sz);
        fread(test_buf, pkt_sz, 1, inf);
        tpid = ((test_buf[1] & 0x1F) << 8) | test_buf[2];
        if(tpid == pid)
            sf->ESGather(pid, test_buf, of);
    }
    fclose(inf);
    fclose(of);
}

uint8_t* TSAnalysis::get_ts(uint16_t pid, uint32_t pkt_idx)
{
    if(pkt_sz == 0)
        return NULL;

    uint8_t* ts = new uint8_t[pkt_sz];
    FILE* fp = fopen(in_ts_file, "rb");
    if(fp != NULL)
    {
        fseek(fp, st_idx + pkt_idx * pkt_sz, SEEK_SET);
        fread(ts, pkt_sz, 1, fp);
        fclose(fp);
        return ts;
    }

    return NULL;
}

void TSAnalysis::ts_analysis()
{
    uint16_t pid;
    uint8_t test_buf[TS_MAX_PACKET_SIZE * 6] = {0};
    /*if(inf == NULL)
    return ;

    clearerr(inf);
    fseek(inf, 0, SEEK_SET);*/
    inf = fopen(in_ts_file, "rb");
    fread((char*)test_buf, TS_MAX_PACKET_SIZE * 6, 1, inf);

    analyzing = true;

    pkt_sz = get_packet_size(test_buf, TS_MAX_PACKET_SIZE * 6, &st_idx);
    if(pkt_sz == -1)
    {
        std::cout << "can't find the sync-byte and can't analysis the TS!\n";
        analyzing = false;
        return ;
    }

    fseek(inf, st_idx, SEEK_SET);
    //inf.seekg(st_idx, inf.beg);
    sf = TSFactory::GetInstance();
    while(!feof(inf))
    {
        try
        {
            //inf.read((char*)test_buf, pkt_sz);
            fread(test_buf, pkt_sz, 1, inf);
            if(test_buf[0] != 0x47)
                throw new SyncErr();

            pid = ((test_buf[1] & 0x1F) << 8) | test_buf[2];

            sf->TSGather(pid, test_buf);
        }
        catch(SyncErr* se)
        {
            set_err_timepos(se);
            int idx = synchronous(se);
            if(idx == -1)
            {
                std::cout << "fatal error! can't find sync-byte, analysis will terminate..." << std::endl;
                return ;
            }
            ++ts_err.level1_err;
            ++ts_err.err;
        }
        catch(PatErr* pe)
        {
            set_err_timepos(pe);
            if(pe->type = PatErr::PTID)
            {
                pe->des_idx = 2;
                ++ts_err.pat_tid_err;
            }
            if(pe->type = PatErr::PINTV)
            {
                pe->des_idx = 3;
                ++ts_err.pat_intv_err;
            }
            if(pe->type = PatErr::PSRB)
            {
                pe->des_idx = 4;
                ++ts_err.pat_srb_err;
            }       
            ts_err.err_lmq.push_back(pe);
            ++ts_err.pat_err;
            ++ts_err.level1_err;
            ++ts_err.err;
        }
        catch(CCErr* ce)
        {
            char info[32] = {0};
            sprintf(info, "PID = 0x%x", pid);
            set_err_timepos(ce);
            ce->des_idx = 5;
            ts_err.err_lmq.push_back(ce);
            ++ts_err.cc_err;
            ++ts_err.level1_err;
            ++ts_err.err;
            //++ps[pid].cc_err_num;
        }
        catch(PmtErr* me)
        {
            set_err_timepos(me);
            if(me->type = PmtErr::PINTV)
            {
                me->des_idx = 6;
                ++ts_err.pmt_intv_err;
            }
            if(me->type = PmtErr::PSRB)
            {
                me->des_idx = 7;
                ++ts_err.pmt_srb_err;
            }
            ts_err.err_lmq.push_back(me);
            ++ts_err.pmt_err;
            ++ts_err.level1_err;
            ++ts_err.err;
        }
        catch(TransErr* te)
        {
            set_err_timepos(te);
            te->des_idx = 8;
            ts_err.err_lmq.push_back(te);
            ++ts_err.trans_err;
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(CrcErr* ce)
        {
            set_err_timepos(ce);
            if(ce->type == CrcErr::CPAT)
            {
                ce->des_idx = 9;
                ++ts_err.crc_pat_err;
            }
            if(ce->type == CrcErr::CPMT)
            {
                ce->des_idx = 11;
                ++ts_err.crc_pmt_err;
            }
            if(ce->type == CrcErr::CCAT)
            {
                ce->des_idx = 10;
                ++ts_err.crc_cat_err;
            }
            if(ce->type == CrcErr::CNIT)
            {
                ce->des_idx = 12;
                ++ts_err.crc_nit_err;
            }
            if(ce->type == CrcErr::CEIT)
            {
                ce->des_idx = 16;
                ++ts_err.crc_eit_err;
            }
            if(ce->type == CrcErr::CBAT)
            {
                ce->des_idx = 14;
                ++ts_err.crc_bat_err;
            }
            if(ce->type == CrcErr::CSDT)
            {
                ce->des_idx = 9;
                ++ts_err.crc_sdt_err;
            }
            if(ce->type == CrcErr::CTOT)
            {
                ce->des_idx = 15;
                ++ts_err.crc_tot_err;
            }
            ts_err.err_lmq.push_back(ce);
            ++ts_err.crc_err;
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(PcrIntvErr* pie)
        {
            set_err_timepos(pie);
            pie->des_idx = 17;
            ts_err.err_lmq.push_back(pie);
            ++ts_err.pcr_intv_err;
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(PcrDisErr* pde)
        {
            set_err_timepos(pde);
            pde->des_idx = 18;
            ts_err.err_lmq.push_back(pde);
            ++ts_err.pcr_disc_err;
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(PcrAcuErr* pae)
        {
            set_err_timepos(pae);
            pae->des_idx = 19;
            ts_err.err_lmq.push_back(pae);
            ++ts_err.pcr_acu_err;
            ++ts_err.level2_err;
            ++ts_err.err;
            //std::cout << ts_err.pcr_acu_err << std::endl;
        }
        catch(PtsErr* pte)
        {
            set_err_timepos(pte);
            pte->des_idx = 20;
            ts_err.err_lmq.push_back(pte);
            ++ts_err.pts_err;
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(CatErr* ae)
        {
            set_err_timepos(ae);
            if(ae->type == CatErr::CSRB)
            {
                ae->des_idx = 21;
                ++ts_err.cat_srb_err;
            }
            if(ae->type == CatErr::CTID)
            {
                ae->des_idx = 22;
                ++ts_err.cat_tid_err;
            }
            ts_err.err_lmq.push_back(ae);
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(DsmccErr&)
        {

        }   
    }

    std::list<ESGInfo*>::iterator esit = sf->esg_list.begin();
    for(; esit != sf->esg_list.end(); ++esit)
    {
        delete (*esit);
    }
    sf->esg_list.clear();

    fclose(inf);
    analyzing = false;
}