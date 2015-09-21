#ifndef _EXCP_H_
#define _EXCP_H_

#include <string>

static char* ts_err_desc[][2] = 
{
    "ͬ����ʧ����", "TSͬ���ֽ�0x47��ʧ", // 0
    "ͬ���ֽڴ���", "TSͬ���ֽڲ�����0x47", // 1
    "PAT����", "PID=0x0��table_id������0x0", // 2
    "PAT����", "PAT�������0.5��", // 3
    "PAT����", "PID=0��TS������ָʾ������0", // 4
    "������������", "TS��������������", // 5
    "PMT����", "PMT�������0.5��", //6
    "PMT����", "PID=PMT_PID��TS������ָʾ������0", // 7

    "�������", "TS���������ָʾΪ1", //8
    "CRC����", "PAT����CRC����", // 9
    "CRC����", "CAT����CRC����", // 10
    "CRC����", "PMT����CRC����", // 11
    "CRC����", "NIT����CRC����", // 12
    "CRC����", "SDT����CRC����", // 13
    "CRC����", "BAT����CRC����", // 14
    "CRC����", "TOT����CRC����", // 15
    "CRC����", "EIT����CRC����", // 16
    "PCR�������", "PCR�������40ms", // 17
    "PCR����������", "δ���ò�������־��PCR�������100ms", //18
    "PCR���ȴ���", "PCR���ȳ�������500ns", // 19
    "PTS����", "PTS�������700ms", // 20
    "CAT����", "��������δ����CATȴ���ڼ��ű�־��Ϊ0��TS��", // 21
    "CAT����", "PID=0x1��table_id������0x1" // 22

};

class TsErr
{
public:
    TsErr(uint16_t p = 0xFFFF) : pid(p){}
    std::string pos;
    std::string time;
    int des_idx;
    uint16_t pid;

    virtual ~TsErr(){};
};

class SyncErr : public TsErr
{
public:
   SyncErr() : TsErr() {}
};

class PatErr : public TsErr
{
public: 
    enum pat_type {PTID = 0, PINTV, PSRB};
    pat_type type;

    PatErr(pat_type tp) : TsErr(), type(tp){}
    virtual ~PatErr(){}
};

class CCErr : public TsErr
{
public:
    CCErr(uint16_t p) : TsErr(p){}
};

class PmtErr : public TsErr
{
public:
    enum pmt_type {PINTV = 0, PSRB};
    pmt_type type;

    PmtErr(pmt_type tp) : TsErr(), type(tp){}
    virtual ~PmtErr(){}
};

class TransErr : public TsErr
{
public:
    TransErr(uint16_t p) : TsErr(p) {}
};

class CrcErr : public TsErr
{
public:
    enum crc_type {CPAT = 0, CPMT, CCAT, CNIT, CEIT, CBAT, CSDT, CTOT};
    crc_type type;

    CrcErr(crc_type tp) : TsErr(), type(tp){}
    virtual ~CrcErr(){}
};


class PcrIntvErr : public TsErr
{
public:
    PcrIntvErr(uint16_t p) : TsErr(p) {}
};
class PcrDisErr : public TsErr
{
public:
    PcrDisErr(uint16_t p) : TsErr(p) {}
};
class PcrAcuErr : public TsErr
{
public:
    PcrAcuErr(uint16_t p) : TsErr(p) {}
};

class PtsErr : public TsErr
{
public:
    PtsErr(uint16_t p) : TsErr(p) {}
};

class CatErr : public TsErr
{
public:
    enum cat_type {CTID = 0, CSRB};
    cat_type type;
    
    CatErr(cat_type tp) : TsErr(), type(tp){}
    virtual ~CatErr(){}
};

class DsmccErr : public TsErr{};

#endif