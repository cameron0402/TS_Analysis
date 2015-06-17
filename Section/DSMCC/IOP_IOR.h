#ifndef _IOP_IOR_H_
#define _IOP_IOR_H_

#include "../../def.h"
#include "BIOPProfile.h"

class IOP_IOR
{
public:
    IOP_IOR();
    IOP_IOR(uint8_t* data);
    virtual ~IOP_IOR();

    uint32_t typeID_length;
    uint8_t typeID[4];

    uint32_t tagged_profiles_count;

    std::list<BIOPProfile*> biop_pf_list;

    uint32_t iop_ior_length;

};

#endif