#include "AnnouncementSupportDesc.h"

//##ModelId=555C4D93028C
AnnouncementSupportDesc::AnnouncementSupportDesc()
{
}

//##ModelId=555C4D9502A4
AnnouncementSupportDesc::AnnouncementSupportDesc(uint8_t* data)
    : Descriptor(data),
      announcement_support_indicator((data[2] << 8) | data[3])
{
    AnnounceInfo tmp;
    int index = 4;
    while(index < length + 2)
    {
        tmp.announcement_type = data[index] >> 4;
        tmp.reference_type = data[index] & 0x07;
        index += 1;
        if(tmp.reference_type >= 0x01 && tmp.reference_type <= 0x03)
        {
            tmp.original_network_id = (data[index] << 8) | data[index + 1];
            tmp.transport_stream_id = (data[index + 2] << 8) | data[index + 3];
            tmp.service_id = (data[index + 4] << 8) | data[index + 5];
            tmp.component_tag = data[index + 6];
            index += 6;
        }
        announce_list.push_back(tmp);
    }
}

//##ModelId=555C4D97023C
AnnouncementSupportDesc::~AnnouncementSupportDesc()
{
}

