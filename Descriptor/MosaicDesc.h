#ifndef MOSAICDESC_H_HEADER_INCLUDED_AAA50E21
#define MOSAICDESC_H_HEADER_INCLUDED_AAA50E21
#include "Descriptor.h"

//descriptor_tag = 0x51
//##ModelId=555AE40D03E6
class MosaicDesc : public Descriptor
{
  public:
    //##ModelId=555AE9890204
    class MosaicInfo
    {
      public:
        //##ModelId=555AE9970345
        uint8_t logical_cell_id;
        //##ModelId=555AE9CC01F3
        uint8_t logical_cell_presentation_info;

        uint8_t elementary_cell_field_length;
        //##ModelId=555AE9F800C3
        std::list<uint8_t> elem_id_list;
        //##ModelId=555AEA21034C
        uint8_t cell_linkage_info;
        //##ModelId=555AEA3803AC
        uint16_t bouquet_id;
        //##ModelId=555AEA4E0255
        uint16_t original_network_id;
        //##ModelId=555AEA670084
        uint16_t transport_stream_id;
        //##ModelId=555AEA7F0114
        uint16_t service_id;
        //##ModelId=555AEA9902F6
        uint16_t event_id;
    };

    //##ModelId=555AEAE300AB
    MosaicDesc();

    //##ModelId=555AEAF302B3
    MosaicDesc(uint8_t* data);

    //##ModelId=555AEB0C003B
    virtual ~MosaicDesc();

    //##ModelId=555AE423015A
    uint8_t mosaic_entry_point;
    //##ModelId=555AE8A20115
    uint8_t number_of_horizontal_elementary_cells;
    //##ModelId=555AE8C202BB
    uint8_t number_of_vertical_elementary_cells;
    //##ModelId=555AEAB70302
    std::list<MosaicInfo> mosaic_list;
};



#endif /* MOSAICDESC_H_HEADER_INCLUDED_AAA50E21 */
