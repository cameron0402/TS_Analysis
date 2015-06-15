#ifndef CELLLISTDESC_H_HEADER_INCLUDED_AAA2ECE3
#define CELLLISTDESC_H_HEADER_INCLUDED_AAA2ECE3
#include "../Descriptor.h"

// descriptor_tag = 0x6C
//##ModelId=555D2C8200D1
class CellListDesc : public Descriptor
{
  public:
    //##ModelId=555D2D040094
    class CellInfo
    {
      public:
        //##ModelId=555D2DCD01C1
        class SubCellInfo
        {
          public:
            //##ModelId=555D2DD90365
            uint8_t cell_id_extension;
            //##ModelId=555D2DF10317
            uint16_t subcell_latitude;
            //##ModelId=555D2E07031B
            uint16_t subcell_longitude;
            //##ModelId=555D2E20026A
            uint16_t subcell_extend_of_latitude;
            //##ModelId=555D2E3701A0
            uint16_t subcell_extend_of_longitude;
        };

        //##ModelId=555D2D1200D0
        uint16_t cell_id;
        //##ModelId=555D2D2502A7
        uint16_t cell_latitude;
        //##ModelId=555D2D3F01B6
        uint16_t cell_longtitude;
        //##ModelId=555D2D520037
        uint16_t cell_extend_of_latitude;
        //##ModelId=555D2D6E00AD
        uint16_t cell_extend_of_longitude;
        //##ModelId=555D2D9E0088
        uint8_t subcell_info_loop_length;
        //##ModelId=555D2E5C0295
        std::list<SubCellInfo> sub_list;
    };

    //##ModelId=555D2CB000F9
    CellListDesc();

    //##ModelId=555D2CB20349
    CellListDesc(uint8_t* data);

    //##ModelId=555D2CB50069
    virtual ~CellListDesc();

    //##ModelId=555D2EB0010F
    std::list<CellInfo> cell_list;
};



#endif /* CELLLISTDESC_H_HEADER_INCLUDED_AAA2ECE3 */
