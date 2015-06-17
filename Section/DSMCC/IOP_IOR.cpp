#include "IOP_IOR.h"

IOP_IOR::IOP_IOR()
{

}

IOP_IOR::IOP_IOR(uint8_t* data)
    : typeID_length((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]),
      tagged_profiles_count(data[4 + typeID_length]),
      iop_ior_length(0)
{
    memcpy(typeID, data + 4, 4);
    int i;
    int idx = 5 + typeID_length;
    for(i = 0; i < tagged_profiles_count; ++i)
    {
        BIOPProfile* bf = new BIOPProfile(data + idx);
        biop_pf_list.push_back(bf);
        idx += bf->profile_data_length + 4;
    }
    iop_ior_length = idx;
}

IOP_IOR::~IOP_IOR()
{
    std::list<BIOPProfile*>::iterator pit;
    for(pit = biop_pf_list.begin(); pit != biop_pf_list.end(); ++pit)
        delete (*pit);
}