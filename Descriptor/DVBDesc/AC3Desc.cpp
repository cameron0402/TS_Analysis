#include "AC3Desc.h"

//##ModelId=555C46F500D3
AC3Desc::AC3Desc()
{
}

//##ModelId=555C46F70063
AC3Desc::AC3Desc(uint8_t* data)
    : Descriptor(data),
      component_type_flag(data[2] >> 7),
      bsid_flag((data[2] >> 6) & 0x01),
      mainid_flag((data[2] >> 5) & 0x01),
      asvc_flag((data[2] >> 4) & 0x01)
{
    int index = 3;
    if(component_type_flag)
    {
        component_type = data[index++];
    }
    if(bsid_flag)
    {
        bsid = data[index++];
    }
    if(mainid_flag)
    {
        mainid = data[index++];
    }
    if(asvc_flag)
    {
        asvc = data[index++];
    }

    add_info = new uint8_t[length + 2 - index];
    memcpy(add_info, data + index, length + 2 - index);
}

//##ModelId=555C46F900CC
AC3Desc::~AC3Desc()
{
    delete []add_info;
}

