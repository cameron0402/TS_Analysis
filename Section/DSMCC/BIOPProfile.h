#ifndef _BIOP_PROFILE_H_
#define _BIOP_PROFILE_H_

#include "../../def.h"

class BIOP_ObjectLocation
{
public:
    BIOP_ObjectLocation();
    BIOP_ObjectLocation(uint8_t* data);
    virtual ~BIOP_ObjectLocation();

    uint32_t componentID_tag; //0x49534F50  TAG_ObjectLocation
    uint8_t component_data_length;
    uint32_t carouselID; 
    uint16_t moduleID;
    uint8_t major_version; // 0x01 BIOP 协议主版本 1
    uint8_t minor_version; // 0x00 BIOP 协议副版本 0
    uint8_t object_key_length;
    uint8_t* object_key;
};

class DSM_ConnBinder
{
public:
    class BIOP_Tap1
    {
    public:
        BIOP_Tap1();
        BIOP_Tap1(uint8_t* data);
        ~BIOP_Tap1();

        uint16_t id;
        uint16_t use; //0x0016 BIOP_DELIVERY_PARA_USE
        uint16_t association_tag;
        uint8_t selector_length; // 0x0A
        uint16_t selector_type; //0x01
        uint32_t transactionID;
        uint32_t timeout;
    };

    class BIOP_Tap2
    {
    public:
        BIOP_Tap2();
        BIOP_Tap2(uint8_t* data);
        ~BIOP_Tap2();

        uint16_t id;
        uint16_t use; //0x0016 BIOP_DELIVERY_PARA_USE
        uint16_t association_tag;
        uint8_t selector_length; 
        uint8_t* selector;
    };

    DSM_ConnBinder();
    DSM_ConnBinder(uint8_t* data);
    virtual ~DSM_ConnBinder();

    uint32_t componentID_tag; //0x49534F40 TAG_ConnBinder
    uint8_t component_data_length;
    uint8_t taps_count;
    BIOP_Tap1* biop_tap1;
    std::list<BIOP_Tap2*> biop_tap2_list;
};

class BIOP_LiteComponent
{
public:
    BIOP_LiteComponent();
    BIOP_LiteComponent(uint8_t *data);
    virtual ~BIOP_LiteComponent();

    uint32_t componentID_tag; 
    uint8_t component_data_length;
    uint8_t* componet_data;
};

class BIOPProfile
{
public:
    BIOPProfile();
    BIOPProfile(uint8_t* data);
    virtual ~BIOPProfile();

    uint32_t profileID_tag;  //0x49534F06 TAG_BIOP(BIOP Profile Body)
    uint32_t profile_data_length;
    uint8_t profile_data_byte_order; //0x00 big endian
    uint8_t lite_components_count;
    BIOP_ObjectLocation* biop_objloc;
    DSM_ConnBinder* dsm_connb;
    std::list<BIOP_LiteComponent*> biop_lite_list;
};

#endif