#include "TelephoneDesc.h"

//##ModelId=555BDFDB0278
TelephoneDesc::TelephoneDesc()
{
}

//##ModelId=555BDFE60257
TelephoneDesc::TelephoneDesc(uint8_t* data)
    : Descriptor(data),
      foreign_availability((data[2] >> 5) & 0x1),
      connection_type(data[2] & 0x1F),
      country_prefix_length((data[3] >> 5) & 0x03),
      international_area_code_length((data[3] >> 2) & 0x07),
      operator_code_length(data[3] & 0x03),
      national_area_code_length((data[4] >> 4) & 0x07),
      core_number_length(data[4] & 0x0F)
{
    int index = 5;
    country_prefix = new uint8_t[country_prefix_length];
    memcpy(country_prefix, data + index, country_prefix_length);
    index += country_prefix_length;

    international_area_code = new uint8_t[international_area_code_length];
    memcpy(international_area_code, data + index, international_area_code_length);
    index += international_area_code_length;

    operator_code = new uint8_t[operator_code_length];
    memcpy(operator_code, data + index, operator_code_length);
    index += operator_code_length;

    national_area_code = new uint8_t[national_area_code_length];
    memcpy(national_area_code, data + index, national_area_code_length);
    index += operator_code_length;

    core_number = new uint8_t[core_number_length];
    memcpy(core_number, data + index, core_number_length);
}

//##ModelId=555BE0030212
TelephoneDesc::~TelephoneDesc()
{
    delete []country_prefix;
    delete []international_area_code;
    delete []operator_code;
    delete []national_area_code;
    delete []core_number;
}

