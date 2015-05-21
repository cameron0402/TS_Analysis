#include "CellListDesc.h"

//##ModelId=555D2CB000F9
CellListDesc::CellListDesc()
{
}

//##ModelId=555D2CB20349
CellListDesc::CellListDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    CellInfo ci;
    while(index < length + 2)
    {
        ci.cell_id = (data[index] << 8) | data[index + 1];
        ci.cell_latitude = (data[index + 2] << 8) | data[index + 3];
        ci.cell_longtitude = (data[index + 4] << 8) | data[index + 5];
        ci.cell_extend_of_latitude = (data[index + 6] << 4) | (data[index + 7] >> 4);
        ci.cell_extend_of_longitude = ((data[index + 7] & 0x0F) << 8) | data[index + 8];
        ci.subcell_info_loop_length = data[index + 9];
        index += 10;
        int sidx = 0;
        CellInfo::SubCellInfo sci;
        while(sidx < ci.subcell_info_loop_length)
        {
            sci.cell_id_extension = data[index + sidx];
            sci.subcell_latitude = (data[index + sidx + 1] << 8) | data[index + sidx + 2];
            sci.subcell_longitude = (data[index + sidx + 3] << 8) | data[index + sidx + 4];
            sci.subcell_extend_of_latitude = (data[index + sidx + 5] << 4) | (data[index + sidx + 6] >> 4);
            sci.subcell_extend_of_longitude = ((data[index + sidx + 6] & 0x0F) << 4) | data[index + sidx + 7];
            sidx += 8;
            ci.sub_list.push_back(sci);
        }
        index += ci.subcell_info_loop_length;
        cell_list.push_back(ci);
    }
}

//##ModelId=555D2CB50069
CellListDesc::~CellListDesc()
{
}

