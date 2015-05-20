#include "MosaicDesc.h"

//##ModelId=555AEAE300AB
MosaicDesc::MosaicDesc()
{
}

//##ModelId=555AEAF302B3
MosaicDesc::MosaicDesc(uint8_t* data)
    : Descriptor(data),
      mosaic_entry_point(data[2] >> 7),
      number_of_horizontal_elementary_cells((data[2] >> 4) & 0x07),
      number_of_vertical_elementary_cells(data[2] & 0x07)
{
    int index = 3;
    MosaicInfo tmp;
    while(index < length + 2)
    {
        tmp.logical_cell_id = data[index] >> 2;
        tmp.logical_cell_presentation_info = data[index + 1] & 0x07;
        tmp.elementary_cell_field_length = data[index + 2];
        index += 3;
        for(int i = 0; i < tmp.elementary_cell_field_length; i++)
        {
            tmp.elem_id_list.push_back(data[index + i] & 0x3F);
        }
        index += tmp.elementary_cell_field_length;
        tmp.cell_linkage_info = data[index];
        index++;
        switch(tmp.cell_linkage_info)
        {
            case 0x01:
                tmp.bouquet_id = (data[index] << 8) | data[index + 1];
                index += 2;
                break;
            case 0x02:
            case 0x03:
            case 0x04:
                tmp.original_network_id = (data[index] << 8) | data[index + 1];
                tmp.transport_stream_id = (data[index + 2] << 8) | data[index + 3];
                tmp.service_id = (data[index + 4] << 8) | data[index + 5];
                index += 6;
                break;
            default:
                break;
        }
        if(tmp.cell_linkage_info == 0x04)
        {
            tmp.event_id = (data[index] << 8) | data[index + 1];
            index += 2;
        }
        mosaic_list.push_back(tmp);
    }
}

//##ModelId=555AEB0C003B
MosaicDesc::~MosaicDesc()
{
}

