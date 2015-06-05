#ifndef _ADAPTATION_FIELD_H_
#define _ADAPTATION_FIELD_H_

#include "../def.h"

class AdaptationField
{
public:

    AdaptationField();
    ~AdaptationField();

    uint8_t adaptation_field_length;  //8 bit

    bool discontinuity_indicator; //1 bit
    bool random_access_indicator; //1 bit
    bool elementary_stream_priority_indicator; //1 bit
    bool PCR_flag; //1 bit
    bool OPCR_flag; //1 bit
    bool splicing_pointer_flag; //1 bit
    bool transport_private_data_flag; //1 bit
    bool adaptation_field_extension_flag; //1 bit

    //PCR_flag == true
    uint64_t program_clock_reference_base; //33 bit
    uint16_t program_clock_reference_extension; // 9 bit

    //OPCR_flag == true
    uint64_t original_program_clock_reference_base; //33 bit
    uint16_t original_program_clock_reference_extension; // 9 bit

    //splicing_pointer_flag == true
    uint8_t splice_countdown; //8 bit
    
    //transport_private_data_flag == true
    uint8_t transport_private_data_length; //8 bit
    uint8_t* transport_private_data;

    //adaptation_field_extension_flag == 1
    uint8_t adaptation_field_extension_length; //8 bit
    bool ltw_flag; //1 bit
    bool piecewise_rate_flag; //1 bit
    bool seamless_splice_flag; //1 bit

    //ltw_flag == true
    bool ltw_valid_flag; //1 bit
    uint16_t ltw_offset; //15 bit

    //piecewise_rate_flag == true
    uint32_t piecewise_rate; //22 bit

    //seamless_splice_flag == true
    uint8_t splice_type; //4 bit
    uint64_t DTS_next_AU; //33 bit, composed by 3 parts 
};

#endif