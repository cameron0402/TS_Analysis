#include "BIOPProfile.h"

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
    object_key = new uint8_t[object_key_length];
    memcpy(object_key, data + 14, object_key_length);
}

BIOP_ObjectLocation::~BIOP_ObjectLocation()
{
    if(object_key != NULL)
        delete []object_key;
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