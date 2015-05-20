#include "VBIDataDesc.h"

//##ModelId=5559A20103A9
VBIDataDesc::VBIDataDesc()
{
}

//##ModelId=5559A209018B
VBIDataDesc::VBIDataDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    DataService ds;
    while(index < length + 2)
    {
        ds.data_service_id = data[index];
        ds.data_service_descriptor_length = data[index + 1];
        if(ds.data_service_descriptor_length >= 0x01 && 
           ds.data_service_descriptor_length <= 0x07)
        {
            DataService::DataInfo di;
            uint8_t* dt = data + index + 2;
            int ix = 0;
            while(ix < ds.data_service_descriptor_length)
            {
                di.field_parity = (dt[ix] >> 5) & 0x01;
                di.line_offset = dt[ix] & 0x1F;
                ds.data_list.push_back(di);
                ix += 1;
            }
        }
        data_serv_list.push_back(ds);
        index += 2 + ds.data_service_descriptor_length;
    }
}

//##ModelId=5559A22100A3
VBIDataDesc::~VBIDataDesc()
{
}

