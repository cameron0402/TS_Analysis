#ifndef _PES_H_
#define _PES_H_

#include "../def.h"

class PES
{
public:
    PES();
    PES(uint32_t raw_len);
    ~PES();

    void Reset();
    void getDetail();

    uint32_t packet_start_code_prefix; //24 bit
    uint8_t stream_id; // 8 bit
    uint16_t PES_packet_length; //16 bit

    //////////
    uint8_t PES_scrambling_control; //2 bit
    uint8_t PES_priority; // 2 bit
    bool data_alignment_indicator; // 1 bit
    bool copyright; // 1 bit
    bool original_or_copy; // 1 bit
    uint8_t PTS_DTS_flags; // 2 bit
    bool ESCR_flag; // 1 bit
    bool ES_rate_flag; // 1 bit
    bool DSM_trick_mode_flag; //1 bit
    bool additional_copy_info_flag; // 1 bit
    bool PES_CRC_flag; //1 bit
    bool PES_extension_flag; // 1 bit
    uint8_t PES_header_data_length; //8 bit

    //PTS_DTS_flag != 00
    uint64_t PTS; // 33 bit
    uint64_t DTS; // 33 bit

    //ESCR_flag == true
    uint64_t ESCR_base; // 33 bit
    uint16_t ESCR_extension; //9 bit

    //ES_rate_flag == true
    uint32_t ES_rate; // 22 bit

    //DSM_trick_mode_flag
    uint8_t trick_mode_control; //3 bit

    uint8_t field_id; // 2 bit
    uint8_t intra_slice_refresh; // 1 bit
    uint8_t frequency_truncation; // 2 bit
    uint8_t rep_cntrl; //5 bit

    //additional_copy_info_flag == true
    uint8_t additional_copy_info; // 7 bit

    //PES_CRC_flag == 1
    uint16_t previous_PES_packet_CRC;

    //PES_extension_flag == true
    bool PES_private_data_flag; // 1 bit
    bool pack_header_field_flag; // 1 bit
    bool program_packet_sequence_counter_flag; // 1 bit
    bool P_STD_buffer_flag; // 1 bit
    bool PES_extension_flag_2; // 1 bit

    //PES_private_data_flag == true
    uint8_t PES_private_data[16]; // 128 bit

    //pack_header_field_flag
    uint8_t pack_field_length; // 8 bit
    uint8_t* pack_header;

    //program_packer_sequence_counter_flag == true
    uint8_t program_packet_sequence_counter; // 7 bit
    uint8_t MPEG1_MPEG2_indentifier; // 1 bit
    uint8_t original_stuff_length; // 6 bit

    //p_STD_buffer_flag == true
    uint8_t P_STD_buffer_scale; // 1 bit
    uint16_t P_STD_buffer_size; // 13 bit

    //PES_extension_flag_2 == true
    uint8_t PES_extension_field_length;

    uint8_t* PES_packet_data;

    uint8_t* raw_data;
    uint32_t raw_pes_length;
    uint32_t recv_length;
};

#endif