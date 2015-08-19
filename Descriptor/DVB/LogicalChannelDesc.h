#ifndef _LOGICAL_CHANNEL_DESC_
#define _LOGICAL_CHANNEL_DESC_

#include "../Descriptor.h"
//descriptor_tag = 0x83
class LogicalChannelDesc : public Descriptor
{
public:
    class LogicInfo
    {
    public:
        LogicInfo(uint8_t* data);
        ~LogicInfo();

        uint16_t service_id;
        bool visible_service_flag;
        uint16_t logical_channel_number;
    };

    LogicalChannelDesc(uint8_t* data);
    ~LogicalChannelDesc();

    std::list<LogicInfo*> loginfo_list;
};

#endif