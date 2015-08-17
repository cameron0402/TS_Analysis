#include "TSAnalysis.h"
#include "../Section/PSI_SI/PAT.h"
#include "../Section/PSI_SI/PMT.h"

TSAnalysis::TSAnalysis(char* infile)
    : ts_err(),
      err_xml(new TiXmlElement("ERROR_LOG")),
      sf(NULL),
      in_ts_file(infile),
      inf(infile, std::ifstream::binary),
      analyzing(false)
{
}


TSAnalysis::~TSAnalysis()
{
    if(err_xml != NULL)
        delete err_xml;
    if(sf != NULL)
    {
        delete sf;
        sf = NULL;
    }
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

int TSAnalysis::synchronous()
{
    int idx = 0;
    char buf[TS_MAX_PACKET_SIZE * 6] = {0};
    inf.seekg(-pkt_sz, inf.cur);

    TiXmlElement* err = new TiXmlElement("err");
    err->SetAttribute("num", ts_err.err);
    err->SetAttribute("time", inf.tellg());
    err->SetAttribute("pos", "");

    inf.read(buf, TS_MAX_PACKET_SIZE * 6);

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
                    err->SetAttribute("type", "ͬ���ֽڴ���");
                    err->SetAttribute("desc", "TSͬ���ֽڲ�����0x47");
                }
                else
                {
                    ++ts_err.sync_loss_err;
                    err->SetAttribute("type", "ͬ����ʧ����");
                    err->SetAttribute("desc", "TSͬ���ֽ�0x47��ʧ");
                }

                err_xml->LinkEndChild(err);
                
                inf.seekg(idx - TS_MAX_PACKET_SIZE * 6, inf.cur);

                return idx;
            }
        }
        ++idx;
    }

    return -1;
}

void TSAnalysis::save_es(int pid, char* es_file)
{
    uint16_t tpid;
    uint8_t test_buf[TS_MAX_PACKET_SIZE * 6] = {0};
    inf.seekg(0, inf.beg);
    inf.read((char*)test_buf, TS_MAX_PACKET_SIZE * 6);
    std::ofstream of(es_file, std::ios_base::binary);

    int st_idx = 0;
    int pkt_sz = 0;
    pkt_sz = get_packet_size(test_buf, TS_MAX_PACKET_SIZE * 6, &st_idx);
    if(pkt_sz == -1)
    {
        std::cout << "can't find the sync-byte and can't analysis the TS!\n";
        return ;
    }

    inf.seekg(st_idx, inf.beg);
    sf = TSFactory::GetInstance();
    while(!inf.eof())
    {
        inf.read((char*)test_buf, pkt_sz);
        tpid = ((test_buf[1] & 0x1F) << 8) | test_buf[2];
        if(tpid == pid)
            sf->ESGather(pid, test_buf, of);
    }
}

void TSAnalysis::ts_analysis()
{
    uint16_t pid;
    uint8_t test_buf[TS_MAX_PACKET_SIZE * 6] = {0};
    inf.seekg(0, inf.beg);
    inf.read((char*)test_buf, TS_MAX_PACKET_SIZE * 6);

    analyzing = true;

    int st_idx = 0;
    pkt_sz = get_packet_size(test_buf, TS_MAX_PACKET_SIZE * 6, &st_idx);
    if(pkt_sz == -1)
    {
        std::cout << "can't find the sync-byte and can't analysis the TS!\n";
        analyzing = false;
        return ;
    }

    inf.seekg(st_idx, inf.beg);
    sf = TSFactory::GetInstance();
    while(!inf.eof())
    {
        try
        {
            inf.read((char*)test_buf, pkt_sz);
            if(test_buf[0] != 0x47)
                throw SyncErr();

            pid = ((test_buf[1] & 0x1F) << 8) | test_buf[2];

            sf->TSGather(pid, test_buf);
        }
        catch(SyncErr&)
        {
            int idx = synchronous();
            if(idx == -1)
            {
                std::cout << "fatal error! can't find sync-byte, analysis will terminate..." << std::endl;
                return ;
            }
            ++ts_err.level1_err;
            ++ts_err.err;
        }
        catch(PatErr& pe)
        {
            TiXmlElement* err = new TiXmlElement("err");
            err->SetAttribute("num", ts_err.err);
            err->SetAttribute("time", inf.tellg());
            err->SetAttribute("pos", "");
            err->SetAttribute("type", "PAT����");
            if(pe.type = PatErr::PTID)
            {
                err->SetAttribute("desc", "PID=0x0��table_id������0x0");
                ++ts_err.pat_tid_err;
            }
            if(pe.type = PatErr::PINTV)
            {
                err->SetAttribute("desc", "PAT�������0.5��");
                ++ts_err.pat_intv_err;
            }
            if(pe.type = PatErr::PSRB)
            {
                err->SetAttribute("desc", "PID=0��TS������ָʾ������0");
                ++ts_err.pat_srb_err;
            }       
            err_xml->LinkEndChild(err);
            ++ts_err.pat_err;
            ++ts_err.level1_err;
            ++ts_err.err;
        }
        catch(CCErr&)
        {
            char info[32] = {0};
            sprintf(info, "PID = 0x%x", pid);
            TiXmlElement* err = new TiXmlElement("err");
            err->SetAttribute("num", ts_err.err);
            err->SetAttribute("time", inf.tellg());
            err->SetAttribute("pos", info);
            err->SetAttribute("type", "������������");
            err->SetAttribute("desc", "TS��������������");
            err_xml->LinkEndChild(err);
            ++ts_err.cc_err;
            ++ts_err.level1_err;
            ++ts_err.err;
            //++ps[pid].cc_err_num;
        }
        catch(PmtErr& me)
        {
            TiXmlElement* err = new TiXmlElement("err");
            err->SetAttribute("num", ts_err.err);
            err->SetAttribute("time", inf.tellg());
            err->SetAttribute("pos", "");
            err->SetAttribute("type", "PMT����");
            if(me.type = PmtErr::PINTV)
            {
                err->SetAttribute("desc", "PMT�������0.5��");
                ++ts_err.pmt_intv_err;
            }
            if(me.type = PmtErr::PSRB)
            {
                err->SetAttribute("desc", "PID=PMT_PID��TS������ָʾ������0");
                ++ts_err.pmt_srb_err;
            }
            err_xml->LinkEndChild(err);
            ++ts_err.pmt_err;
            ++ts_err.level1_err;
            ++ts_err.err;
        }
        catch(TransErr&)
        {
            TiXmlElement* err = new TiXmlElement("err");
            err->SetAttribute("num", ts_err.err);
            err->SetAttribute("time", inf.tellg());
            err->SetAttribute("pos", "");
            err->SetAttribute("type", "�������");
            err->SetAttribute("desc", "TS���������ָʾΪ1");
            err_xml->LinkEndChild(err);
            ++ts_err.trans_err;
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(CrcErr& ce)
        {
            TiXmlElement* err = new TiXmlElement("err");
            err->SetAttribute("num", ts_err.err);
            err->SetAttribute("time", inf.tellg());
            err->SetAttribute("pos", "");
            err->SetAttribute("type", "CRC����");
            if(ce.type == CrcErr::CPAT)
            {
                err->SetAttribute("desc", "PAT����CRC����");
                ++ts_err.crc_pat_err;
            }
            if(ce.type == CrcErr::CPMT)
            {
                err->SetAttribute("desc", "PMT����CRC����");
                ++ts_err.crc_pmt_err;
            }
            if(ce.type == CrcErr::CCAT)
            {
                err->SetAttribute("desc", "CAT����CRC����");
                ++ts_err.crc_cat_err;
            }
            if(ce.type == CrcErr::CNIT)
            {
                err->SetAttribute("desc", "NIT����CRC����");
                ++ts_err.crc_nit_err;
            }
            if(ce.type == CrcErr::CEIT)
            {
                err->SetAttribute("desc", "EIT����CRC����");
                ++ts_err.crc_eit_err;
            }
            if(ce.type == CrcErr::CBAT)
            {
                err->SetAttribute("desc", "BAT����CRC����");
                ++ts_err.crc_bat_err;
            }
            if(ce.type == CrcErr::CSDT)
            {
                err->SetAttribute("desc", "SDT����CRC����");
                ++ts_err.crc_sdt_err;
            }
            if(ce.type == CrcErr::CTOT)
            {
                err->SetAttribute("desc", "TOT����CRC����");
                ++ts_err.crc_tot_err;
            }
            err_xml->LinkEndChild(err);
            ++ts_err.crc_err;
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(PcrIntvErr&)
        {
            TiXmlElement* err = new TiXmlElement("err");
            err->SetAttribute("num", ts_err.err);
            err->SetAttribute("time", inf.tellg());
            err->SetAttribute("pos", "");
            err->SetAttribute("type", "PCR�������");
            err->SetAttribute("desc", "PCR�������40ms");
            err_xml->LinkEndChild(err);
            ++ts_err.pcr_intv_err;
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(PcrDisErr&)
        {
            TiXmlElement* err = new TiXmlElement("err");
            err->SetAttribute("num", ts_err.err);
            err->SetAttribute("time", inf.tellg());
            err->SetAttribute("pos", "");
            err->SetAttribute("type", "PCR����������");
            err->SetAttribute("desc", "δ���ò�������־��PCR�������100ms");
            err_xml->LinkEndChild(err);
            ++ts_err.pcr_disc_err;
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(PcrAcuErr&)
        {
            TiXmlElement* err = new TiXmlElement("err");
            err->SetAttribute("num", ts_err.err);
            err->SetAttribute("time", inf.tellg());
            err->SetAttribute("pos", "");
            err->SetAttribute("type", "PCR���ȴ���");
            err->SetAttribute("desc", "PCR���ȳ�������500ns");
            err_xml->LinkEndChild(err);
            ++ts_err.pcr_acu_err;
            ++ts_err.level2_err;
            ++ts_err.err;
            //std::cout << ts_err.pcr_acu_err << std::endl;
        }
        catch(PtsErr&)
        {
            TiXmlElement* err = new TiXmlElement("err");
            err->SetAttribute("num", ts_err.err);
            err->SetAttribute("time", inf.tellg());
            err->SetAttribute("pos", "");
            err->SetAttribute("type", "PTS����");
            err->SetAttribute("desc", "PTS�������700ms");
            err_xml->LinkEndChild(err);
            ++ts_err.pts_err;
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(CatErr& ae)
        {
            TiXmlElement* err = new TiXmlElement("err");
            err->SetAttribute("num", ts_err.err);
            err->SetAttribute("time", inf.tellg());
            err->SetAttribute("pos", "");
            err->SetAttribute("type", "CAT����");
            if(ae.type == CatErr::CSRB)
            {
                err->SetAttribute("desc", "��������δ����CATȴ���ڼ��ű�־��Ϊ0��TS��");
                ++ts_err.cat_srb_err;
            }
            if(ae.type == CatErr::CTID)
            {
                err->SetAttribute("desc", "PID=0x1��table_id������0x1");
                ++ts_err.cat_tid_err;
            }
            err_xml->LinkEndChild(err);
            ++ts_err.level2_err;
            ++ts_err.err;
        }
        catch(DsmccErr&)
        {

        }   
    }

    analyzing = false;
}