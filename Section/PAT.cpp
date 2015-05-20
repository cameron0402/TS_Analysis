#include "PAT.h"

//##ModelId=55555EB90262
PAT::PAT()
{
}

//##ModelId=55555EC7002C
PAT::PAT(uint8_t* data, uint16_t len) : Section(data, len)
{
    int index = 8;
    PAT::ProgInfo tmp;
    while(index < len - 4)
    {
        tmp.program_number = (data[index] << 8) | data[index + 1];
        tmp.program_map_PID = (data[index + 2] >> 3) & 0x1F | data[index + 3];
        prog_list.push_back(tmp);
        index += 4;
    }
}

PAT::~PAT()
{

}

