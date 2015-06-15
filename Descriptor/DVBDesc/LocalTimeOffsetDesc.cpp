#include "LocalTimeOffsetDesc.h"

//##ModelId=555BEC1F03B6
LocalTimeOffsetDesc::LocalTimeOffsetDesc()
{
}

//##ModelId=555BEC2A0276
LocalTimeOffsetDesc::LocalTimeOffsetDesc(uint8_t* data) : Descriptor(data)
{
    TimeOffsetInfo tmp;
    int index = 2;
    while(index < length + 2)
    {
        memcpy(tmp.country_code, data + index, 3);
        tmp.country_region_id = data[index + 4] >> 2;
        tmp.local_time_offset_polarity = data[index + 4] & 0x01;
        tmp.local_time_offset = (data[index + 5] << 8) | data[index + 6];
        tmp.time_of_change = (data[index + 7] << 32) | (data[index + 8] << 24) | 
                             (data[index + 9] << 16) | (data[index + 10] << 8) |data[index + 11];
        tmp.next_time_offset = (data[index + 12] << 8) | data[index + 13];
        index += 13;

        timeoff_list.push_back(tmp);
    }
}

//##ModelId=555BEC43035D
LocalTimeOffsetDesc::~LocalTimeOffsetDesc()
{
}

