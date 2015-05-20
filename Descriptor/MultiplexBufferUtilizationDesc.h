#ifndef MULTIPLEXBUFFERUTILIZATIONDESC_H_HEADER_INCLUDED_AAA6FA56
#define MULTIPLEXBUFFERUTILIZATIONDESC_H_HEADER_INCLUDED_AAA6FA56
#include "Descriptor.h"

//descriptor_tag = 0x0C
//##ModelId=55594996025A
class MultiplexBufferUtilizationDesc : public Descriptor
{
  public:
    //##ModelId=55594A2B0077
    MultiplexBufferUtilizationDesc();

    //##ModelId=55594A410077
    MultiplexBufferUtilizationDesc(uint8_t* data);

    //##ModelId=55594A6B0286
    virtual ~MultiplexBufferUtilizationDesc();

    //##ModelId=555949BA006E
    bool mdv_valid_flag;
    //##ModelId=555949D60217
    uint16_t multiplex_delay_variation;
    //##ModelId=555949FD02E7
    uint8_t multiplex_strategy;
};



#endif /* MULTIPLEXBUFFERUTILIZATIONDESC_H_HEADER_INCLUDED_AAA6FA56 */
