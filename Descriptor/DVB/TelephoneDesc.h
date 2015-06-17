#ifndef TELEPHONEDESC_H_HEADER_INCLUDED_AAA45526
#define TELEPHONEDESC_H_HEADER_INCLUDED_AAA45526
#include "../Descriptor.h"

//##ModelId=555BDE49019F
class TelephoneDesc : public Descriptor
{
  public:
    //##ModelId=555BDFDB0278
    TelephoneDesc();

    //##ModelId=555BDFE60257
    TelephoneDesc(uint8_t* data);

    //##ModelId=555BE0030212
    virtual ~TelephoneDesc();

    //##ModelId=555BDEAE02C9
    bool foreign_availability;
    //##ModelId=555BDEC700D0
    uint8_t connection_type;
    //##ModelId=555BDEE202FA
    uint8_t country_prefix_length;
    //##ModelId=555BDEFF02B3
    uint8_t international_area_code_length;
    //##ModelId=555BDF27011C
    uint8_t operator_code_length;
    //##ModelId=555BDF3F0378
    uint8_t national_area_code_length;
    //##ModelId=555BDF650174
    uint8_t core_number_length;
    //##ModelId=555BDF7B0160
    uint8_t* country_prefix;
    //##ModelId=555BDF8F03B7
    uint8_t* international_area_code;
    //##ModelId=555BDFA803E4
    uint8_t* national_area_code;
    //##ModelId=555BDFBF01C3
    uint8_t* core_number;
    //##ModelId=555BE37D01E6
    uint8_t* operator_code;
};



#endif /* TELEPHONEDESC_H_HEADER_INCLUDED_AAA45526 */
