#ifndef VBIDATADESC_H_HEADER_INCLUDED_AAA60BC2
#define VBIDATADESC_H_HEADER_INCLUDED_AAA60BC2
#include "Descriptor.h"

//##ModelId=5559A1140310
class VBIDataDesc : public Descriptor
{
  public:
    //##ModelId=5559A12E010A
    class DataService
    {
      public:
        //##ModelId=5559A4A60053
        class DataInfo
        {
          public:
            //##ModelId=5559A4CF0012
            uint8_t field_parity;
            //##ModelId=5559A4F60012
            uint8_t line_offset;
        };

        //##ModelId=5559A14400EB
        uint8_t data_service_id;
        //##ModelId=5559A1590143
        uint8_t data_service_descriptor_length;
        //##ModelId=5559A53A016B
        std::list<DataInfo> data_list;
    };

    //##ModelId=5559A20103A9
    VBIDataDesc();

    //##ModelId=5559A209018B
    VBIDataDesc(uint8_t* data);

    //##ModelId=5559A22100A3
    virtual ~VBIDataDesc();

    //##ModelId=5559A24A01CA
    std::list<DataService> data_serv_list;
};



#endif /* VBIDATADESC_H_HEADER_INCLUDED_AAA60BC2 */
