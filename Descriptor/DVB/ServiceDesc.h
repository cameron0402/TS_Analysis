#ifndef SERVICEDESC_H_HEADER_INCLUDED_AAA531FF
#define SERVICEDESC_H_HEADER_INCLUDED_AAA531FF
#include "../Descriptor.h"

//业务类型列表
const char* const service_type_table[17] = 
{
    "", 
    "数字电视业务",     "数字音频广播业务", "图文电视业务",   "NVOD 参考业务",
    "NVOD 时移业务",    "马赛克业务",       "PAL 制编码信号", "SECAM 制编码信号",
    "D/D2-MAC",         "调频广播",         "NTSC 制信号",    "数据广播业务",
    "公共接口使用预留", "RCS 映射",         "RCS FLS",        "DVB MHP 业务"
};

//descriptor_tag = 0x48
class ServiceDesc : public Descriptor
{
  public:
    ServiceDesc(uint8_t* data);
    virtual ~ServiceDesc();

    virtual void resolved();

    uint8_t service_type;
    uint8_t service_provider_length;
    uint8_t* service_provider;
    uint8_t service_name_length;
    uint8_t* service_name;
};



#endif /* SERVICEDESC_H_HEADER_INCLUDED_AAA531FF */
