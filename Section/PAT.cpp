#include "PAT.h"
#include "SectionFactory.h"

//##ModelId=55555EB90262
PAT::PAT()
{
}

//##ModelId=55555EC7002C
PAT::PAT(uint8_t* data, uint16_t len) 
    : Section(data, len),
      transport_stream_id((data[3] << 8) | data[4]), 
      version_number((data[5] >> 1) & 0x1F),
      current_next_indicator(data[5] >> 7),
      section_number(data[6]),
      last_section_number(data[7]),
      crc32((data[len - 4] << 24) | (data[len - 3] << 16) | (data[len - 2] << 8) | data[len - 1])
{
    int index = 8;
    while(index < len - 4)
    {
        ProgInfo* pi = new ProgInfo(data + index);
        prog_list.push_back(pi);
        index += 4;
    }
}

//##ModelId=55582871031A
PAT::~PAT()
{
    std::list<ProgInfo*>::iterator pit;
    for(pit = prog_list.begin(); pit != prog_list.end(); ++pit)
    {
        delete (*pit);
    }
    prog_list.clear();
}

//##ModelId=555D78E90265
PAT::ProgInfo::ProgInfo()
{
}

//##ModelId=555D78EB0320
PAT::ProgInfo::ProgInfo(uint8_t* data)
    : program_number((data[0] << 8) | data[1]),
      program_map_PID(((data[2] & 0x1F) << 8) | data[3])
{
}

//##ModelId=555D78EE02D5
PAT::ProgInfo::~ProgInfo()
{
}

bool PAT::joinTo(SectionFactory* sf)
{
    if(sf->pat == NULL)
    {
        sf->pat = this;
        return true;
    }
    return false;
}

bool PAT::operator==(const PAT& pt)
{
    return crc32 == pt.crc32;
}

