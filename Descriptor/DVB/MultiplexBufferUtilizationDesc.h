#ifndef MULTIPLEXBUFFERUTILIZATIONDESC_H_HEADER_INCLUDED_AAA6FA56
#define MULTIPLEXBUFFERUTILIZATIONDESC_H_HEADER_INCLUDED_AAA6FA56
#include "../Descriptor.h"

//descriptor_tag = 0x0C
class MultiplexBufferUtilizationDesc : public Descriptor
{
  public:
    MultiplexBufferUtilizationDesc(uint8_t* data);
    virtual ~MultiplexBufferUtilizationDesc();

    bool mdv_valid_flag;
    uint16_t multiplex_delay_variation;
    uint8_t multiplex_strategy;
};



#endif /* MULTIPLEXBUFFERUTILIZATIONDESC_H_HEADER_INCLUDED_AAA6FA56 */
