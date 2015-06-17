#include "CellFrequencyLinkDesc.h"

//##ModelId=555D36A70015
CellFrequencyLinkDesc::CellFrequencyLinkDesc()
{
}

//##ModelId=555D36AF01DD
CellFrequencyLinkDesc::CellFrequencyLinkDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    FreqInfo fi;
    while(index < length + 2)
    {
        fi.cell_id = (data[index] << 8) | data[index + 1];
        fi.frequency = (data[index + 2] << 24) | (data[index + 3] << 16) | (data[index + 4] << 8) | (data[index + 5]);
        fi.subcell_info_loo_length = data[index + 6];
        index += 7;
        int sidx = 0;
        FreqInfo::FreqExInfo fei;
        while(sidx < fi.subcell_info_loo_length)
        {
            fei.cell_id_extension = data[index + sidx];
            fei.transposer_frequency = (data[index + sidx + 1] << 24) | (data[index + sidx + 2] << 16) |
                                       (data[index + sidx + 3] << 8) | data[index + sidx + 4];
            sidx += 5;
            fi.ex_list.push_back(fei);
        }
        index += fi.subcell_info_loo_length;
        freq_list.push_back(fi);
    }
}

//##ModelId=555D36B102A9
CellFrequencyLinkDesc::~CellFrequencyLinkDesc()
{
}

