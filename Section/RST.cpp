#include "RST.h"

//##ModelId=556423C803A8
RST::RSInfo::RSInfo()
{
}

//##ModelId=556423D00236
RST::RSInfo::RSInfo(uint8_t* data)
    : transport_stream_id((data[0] << 8) | data[1]),
      original_network_id((data[2] << 8) | data[3]),
      service_id((data[4] << 8) | data[5]),
      event_id((data[6] << 8) | data[7]),
      running_status(data[8] & 0x07)
{
}

//##ModelId=556423D60087
RST::RSInfo::~RSInfo()
{
}

//##ModelId=556422E4005E
RST::RST()
{
}

//##ModelId=556422E703BD
RST::RST(uint8_t* data, uint16_t len, uint32_t crc)
    : Section(data, len)
{
    int index = 3;
    while(index < len)
    {
        RSInfo* ri = new RSInfo(data + index);
        rs_list.push_back(ri);
        index += 9;
    }
}

//##ModelId=556422EB02DF
RST::~RST()
{
    std::list<RSInfo*>::iterator rit;
    for(rit = rs_list.begin(); rit != rs_list.end(); ++rit)
    {
        delete (*rit);
    }
    rs_list.clear();
}

