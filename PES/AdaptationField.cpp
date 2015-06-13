#include "AdaptationField.h"

AdaptationField::AdaptationField()
{

}

AdaptationField::AdaptationField(uint8_t* data)
{
    int idx = 0;
    adaptation_field_length = data[idx++];
    if(adaptation_field_length > 0)
    {
        discontinuity_indicator = data[idx] >> 7;
        random_access_indicator = (data[idx] >> 6) & 0x1;
        elementary_stream_priority_indicator = (data[idx] >> 5) & 0x1;
        PCR_flag = (data[idx] >> 4) & 0x1;
        OPCR_flag = (data[idx] >> 3) & 0x1;
        splicing_pointer_flag = (data[idx] >> 2) & 0x1;
        transport_private_data_flag = (data[idx] >> 1) & 0x1;
        adaptation_field_extension_flag = data[idx] & 0x1;
        ++idx;

        if(PCR_flag)
        {
            program_clock_reference_base = ((uint64_t)data[idx] << 25) | (data[idx + 1] << 17) | 
                                           (data[idx + 2] << 9) | (data[idx + 3] << 1) | (data[idx + 4] >> 7);
            program_clock_reference_extension = ((data[idx + 4] & 0x1) << 8) | data[idx + 5];

            idx += 6;
        }

        if(OPCR_flag)
        {
            original_program_clock_reference_base = ((uint64_t)data[idx] << 25) | (data[idx + 1] << 17) | 
                                                    (data[idx + 2] << 9) | (data[idx + 3] << 1) | (data[idx + 4] >> 7);
            original_program_clock_reference_extension = ((data[idx + 4] & 0x1) << 8) | data[idx + 5];

            idx += 6;
        }

        if(splicing_pointer_flag)
        {
            splice_countdown = data[idx++];
        }

        if(transport_private_data_flag)
        {
            transport_private_data_length = data[idx++];
            idx += transport_private_data_length;
        }

        if(adaptation_field_extension_flag)
        {
            adaptation_field_extension_length = data[idx++];
            ltw_flag = data[idx] >> 7;
            piecewise_rate_flag = (data[idx] >> 6) & 0x1;
            seamless_splice_flag = (data[idx] >> 5) & 0x1;
            ++idx;

            if(ltw_flag)
            {
                ltw_valid_flag = data[idx] >> 7;
                ltw_offset = ((data[idx] & 0x7F) << 8) | data[idx + 1];
                idx += 2;
            }

            if(piecewise_rate_flag)
            {
                piecewise_rate = ((data[idx] & 0x3F) << 16) | (data[idx + 1] << 8) | data[idx + 2];
                idx += 3;
            }

            if(seamless_splice_flag)
            {
                splice_type = data[idx] >> 4;
                DTS_next_AU = (((data[idx] >> 1) & 0x7) << 30) | (data[idx + 1] << 22) | 
                              ((data[idx + 2] >> 1) << 15) | (data[idx + 3] << 8) | (data[idx + 4] >> 1);
            }
        }
    }
}

AdaptationField::~AdaptationField()
{
}