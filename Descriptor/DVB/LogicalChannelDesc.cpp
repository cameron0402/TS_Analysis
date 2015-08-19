#include "LogicalChannelDesc.h"

LogicalChannelDesc::LogicInfo::LogicInfo(uint8_t* data)
    : service_id((data[0] << 8) | data[1]),
      visible_service_flag(data[2] >> 7),
      logical_channel_number(((data[2] & 0x03) << 8) | data[3])
{
}

LogicalChannelDesc::LogicInfo::~LogicInfo()
{
}

LogicalChannelDesc::LogicalChannelDesc(uint8_t* data)
    : Descriptor(data),
      loginfo_list()
{
    int idx = 0;
    while(idx < length)
    {
        LogicInfo* lgi = new LogicInfo(data + idx + 2);
        loginfo_list.push_back(lgi);
        idx += 4;
    }
}

LogicalChannelDesc::~LogicalChannelDesc()
{
    std::list<LogicInfo*>::iterator lit = loginfo_list.begin();
    for(; lit != loginfo_list.end(); ++lit)
        delete (*lit);
}