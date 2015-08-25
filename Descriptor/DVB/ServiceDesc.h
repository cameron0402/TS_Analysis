#ifndef SERVICEDESC_H_HEADER_INCLUDED_AAA531FF
#define SERVICEDESC_H_HEADER_INCLUDED_AAA531FF
#include "../Descriptor.h"

//ҵ�������б�
const char* const service_type_table[17] = 
{
    "", 
    "���ֵ���ҵ��",     "������Ƶ�㲥ҵ��", "ͼ�ĵ���ҵ��",   "NVOD �ο�ҵ��",
    "NVOD ʱ��ҵ��",    "������ҵ��",       "PAL �Ʊ����ź�", "SECAM �Ʊ����ź�",
    "D/D2-MAC",         "��Ƶ�㲥",         "NTSC ���ź�",    "���ݹ㲥ҵ��",
    "�����ӿ�ʹ��Ԥ��", "RCS ӳ��",         "RCS FLS",        "DVB MHP ҵ��"
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
