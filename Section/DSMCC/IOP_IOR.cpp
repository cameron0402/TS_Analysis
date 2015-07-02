#include "IOP_IOR.h"

BIOP_Name::BIOP_Name(uint8_t* data)
    : name_component_count(data[0]),
    id_length(data[1]),
    id_data(NULL),
    kind_length(data[2 + id_length]),
    kind_data(NULL)
{
    id_data = new uint8_t[id_length + 1];
    id_data[id_length] = 0;
    memcpy(id_data, data + 2, id_length);

    kind_data = new uint8_t[kind_length + 1];
    kind_data[kind_length] = 0; 
    memcpy(kind_data, data + 3 + id_length, kind_length);
}

BIOP_Name::~BIOP_Name()
{
    if(id_data != NULL)
        delete []id_data;

    if(kind_data != NULL)
        delete []kind_data;
}

BIOP_ObjectLocation::BIOP_ObjectLocation()
{

}

BIOP_ObjectLocation::BIOP_ObjectLocation(uint8_t* data)
    : componentID_tag((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]),
    component_data_length(data[4]),
    carouselID((data[5] << 24) | (data[6] << 16) | (data[7] << 8) | data[8]),
    moduleID((data[9] << 8) | data[10]),
    major_version(data[11]),
    minor_version(data[12]),
    object_key_length(data[13])
{
    object_key = 0;
    for(int i = 0; i < object_key_length; ++i)
    {
        object_key <<= 8;
        object_key |= data[14 + i];
    }
}

BIOP_ObjectLocation::~BIOP_ObjectLocation()
{
}

DSM_ConnBinder::BIOP_Tap1::BIOP_Tap1()
{

}

DSM_ConnBinder::BIOP_Tap1::BIOP_Tap1(uint8_t* data)
    : id((data[0] << 8) | (data[1])),
    use((data[2] << 8) | data[3]),
    association_tag((data[4] << 8) | data[5]),
    selector_length(data[6]),
    selector_type((data[7] << 8) | data[8]),
    transactionID((data[9] << 24) | (data[10] << 16) | (data[11] << 8) | data[12]),
    timeout((data[13] << 24) | (data[14] << 16) | (data[15] << 8) | data[16])
{

}


DSM_ConnBinder::BIOP_Tap1::~BIOP_Tap1()
{

}

DSM_ConnBinder::BIOP_Tap2::BIOP_Tap2()
{

}

DSM_ConnBinder::BIOP_Tap2::BIOP_Tap2(uint8_t* data)
    : id((data[0] << 8) | (data[1])),
    use((data[2] << 8) | data[3]),
    association_tag((data[4] << 8) | data[5]),
    selector_length(data[6])
{
    selector = new uint8_t[selector_length];
    memcpy(selector, data + 7, selector_length);
}

DSM_ConnBinder::BIOP_Tap2::~BIOP_Tap2()
{
    if(selector != NULL)
        delete []selector;
}

DSM_ConnBinder::DSM_ConnBinder()
{

}

DSM_ConnBinder::DSM_ConnBinder(uint8_t* data)
    : componentID_tag((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]),
    component_data_length(data[4]),
    taps_count(data[5])
{
    int idx = 6;
    if(taps_count > 0)
    {
        biop_tap1 = new DSM_ConnBinder::BIOP_Tap1(data + idx);
        idx += 17;
    }

    int tc = taps_count - 1;
    while(tc > 0 && idx < component_data_length + 4)
    {
        DSM_ConnBinder::BIOP_Tap2* bt = new DSM_ConnBinder::BIOP_Tap2(data + idx);
        biop_tap2_list.push_back(bt);
        idx += bt->selector_length + 7;
        --tc;
    }
}

DSM_ConnBinder::~DSM_ConnBinder()
{
    if(biop_tap1 != NULL)
        delete biop_tap1;

    std::list<DSM_ConnBinder::BIOP_Tap2*>::iterator tit;
    for(tit = biop_tap2_list.begin(); tit != biop_tap2_list.end(); ++tit)
        delete (*tit);
}

BIOP_LiteComponent::BIOP_LiteComponent()
{

}

BIOP_LiteComponent::BIOP_LiteComponent(uint8_t* data)
    : componentID_tag((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]),
    component_data_length(data[4])
{
    componet_data = new uint8_t[component_data_length];
    memcpy(componet_data, data + 5, component_data_length);
}

BIOP_LiteComponent::~BIOP_LiteComponent()
{
    if(componet_data != NULL)
        delete []componet_data;
}

BIOPProfile::BIOPProfile()
{

}

BIOPProfile::BIOPProfile(uint8_t* data)
    : profileID_tag((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]),
    profile_data_length((data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]),
    profile_data_byte_order(data[8]),
    lite_components_count(data[9])
{
    int idx = 10;
    if(idx < profile_data_length + 4)
    {
        biop_objloc = new BIOP_ObjectLocation(data + idx);
        idx += biop_objloc->component_data_length + 5;
    }

    if(idx < profile_data_length + 4)
    {
        dsm_connb = new DSM_ConnBinder(data + idx);
        idx += dsm_connb->component_data_length + 4;
    }

    int tc = lite_components_count - 2;
    while(tc > 0 && idx < profile_data_length + 4)
    {
        BIOP_LiteComponent* bl = new BIOP_LiteComponent(data + idx);
        biop_lite_list.push_back(bl);
        --tc;
        idx += bl->component_data_length  + 4;
    }  
}

BIOPProfile::~BIOPProfile()
{
    if(biop_objloc != NULL)
        delete biop_objloc;

    if(dsm_connb != NULL)
        delete dsm_connb;

    std::list<BIOP_LiteComponent*>::iterator cit;
    for(cit = biop_lite_list.begin(); cit != biop_lite_list.end(); ++cit)
        delete (*cit);
}

IOP_IOR::IOP_IOR()
{

}

IOP_IOR::IOP_IOR(uint8_t* data)
    : typeID_length((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]),
      tagged_profiles_count(data[4 + typeID_length] << 24 | data[5 + typeID_length] << 16 |
                            data[6 + typeID_length] << 8 | data[7 + typeID_length]),
      iop_ior_length(0)
{
    memcpy(typeID, data + 4, typeID_length);
    int i;
    int idx = 8 + typeID_length;
    for(i = 0; i < tagged_profiles_count; ++i)
    {
        BIOPProfile* bf = new BIOPProfile(data + idx);
        biop_pf_list.push_back(bf);
        idx += bf->profile_data_length + 8;
    }
    iop_ior_length = idx;
}

IOP_IOR::~IOP_IOR()
{
    std::list<BIOPProfile*>::iterator pit;
    for(pit = biop_pf_list.begin(); pit != biop_pf_list.end(); ++pit)
        delete (*pit);
}