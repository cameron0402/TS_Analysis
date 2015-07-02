#ifndef _EXCP_H_
#define _EXCP_H_

class SyncErr{};

class PatErr
{
public: 
    enum pat_type {PTID = 0, PINTV, PSRB};
    pat_type type;

    PatErr(){}
    PatErr(pat_type tp) : type(tp){}
    ~PatErr(){}
};

class CCErr{};

class PmtErr
{
public:
    enum pmt_type {PINTV = 0, PSRB};
    pmt_type type;

    PmtErr(){}
    PmtErr(pmt_type tp) : type(tp){}
    ~PmtErr(){}
};

class TransErr{};

class CrcErr
{
public:
    enum crc_type {CPAT = 0, CPMT, CCAT, CNIT, CEIT, CBAT, CSDT, CTOT};
    crc_type type;

    CrcErr(){}
    CrcErr(crc_type tp) : type(tp) {}
    ~CrcErr(){}
};


class PcrIntvErr{};
class PcrDisErr{};
class PcrAcuErr{};

class PtsErr{};

class CatErr
{
public:
    enum cat_type {CTID = 0, CSRB};
    cat_type type;
    
    CatErr(){}
    CatErr(cat_type tp) : type(tp){}
    ~CatErr(){}
};

class DsmccErr{};

#endif