#ifndef _EXCP_H_
#define _EXCP_H_

#include <string>

static char* ts_err_desc[][2] = 
{
    "同步丢失错误", "TS同步字节0x47丢失", // 0
    "同步字节错误", "TS同步字节不等于0x47", // 1
    "PAT错误", "PID=0x0但table_id不等于0x0", // 2
    "PAT错误", "PAT间隔大于0.5秒", // 3
    "PAT错误", "PID=0的TS包加扰指示不等于0", // 4
    "连续计数错误", "TS包连续计数错误", // 5
    "PMT错误", "PMT间隔大于0.5秒", //6
    "PMT错误", "PID=PMT_PID的TS包加扰指示不等于0", // 7

    "传输错误", "TS包传输错误指示为1", //8
    "CRC错误", "PAT发生CRC错误", // 9
    "CRC错误", "CAT发生CRC错误", // 10
    "CRC错误", "PMT发生CRC错误", // 11
    "CRC错误", "NIT发生CRC错误", // 12
    "CRC错误", "SDT发生CRC错误", // 13
    "CRC错误", "BAT发生CRC错误", // 14
    "CRC错误", "TOT发生CRC错误", // 15
    "CRC错误", "EIT发生CRC错误", // 16
    "PCR间隔错误", "PCR间隔大于40ms", // 17
    "PCR不连续错误", "未设置不连续标志且PCR间隔大于100ms", //18
    "PCR精度错误", "PCR精度超过正负500ns", // 19
    "PTS错误", "PTS间隔超过700ms", // 20
    "CAT错误", "传输流中未出现CAT却存在加扰标志不为0的TS包", // 21
    "CAT错误", "PID=0x1但table_id不等于0x1" // 22

};

class TsErr
{
public:
    std::string pos;
    std::string time;
    int des_idx;

    virtual ~TsErr(){};
};

class SyncErr : public TsErr{};

class PatErr : public TsErr
{
public: 
    enum pat_type {PTID = 0, PINTV, PSRB};
    pat_type type;

    PatErr(){}
    PatErr(pat_type tp) : type(tp){}
    virtual ~PatErr(){}
};

class CCErr : public TsErr{};

class PmtErr : public TsErr
{
public:
    enum pmt_type {PINTV = 0, PSRB};
    pmt_type type;

    PmtErr(){}
    PmtErr(pmt_type tp) : type(tp){}
    virtual ~PmtErr(){}
};

class TransErr : public TsErr{};

class CrcErr : public TsErr
{
public:
    enum crc_type {CPAT = 0, CPMT, CCAT, CNIT, CEIT, CBAT, CSDT, CTOT};
    crc_type type;

    CrcErr(){}
    CrcErr(crc_type tp) : type(tp) {}
    virtual ~CrcErr(){}
};


class PcrIntvErr : public TsErr{};
class PcrDisErr : public TsErr{};
class PcrAcuErr : public TsErr{};

class PtsErr : public TsErr{};

class CatErr : public TsErr
{
public:
    enum cat_type {CTID = 0, CSRB};
    cat_type type;
    
    CatErr(){}
    CatErr(cat_type tp) : type(tp){}
    virtual ~CatErr(){}
};

class DsmccErr : public TsErr{};

#endif