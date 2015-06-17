#include "DsmccMessageHeader.h"

DsmccMessageHeader::DsmccMessageHeader()
{

}

DsmccMessageHeader::DsmccMessageHeader(uint8_t* data)
    : protocol_discriminator(data[0]),
      dsmcc_type(data[1]),
      messageId((data[2] << 8) | data[3]),
      transactionId((data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]),
      adaptation_length(data[9]),
      message_length((data[10] << 8) | data[11])
{

}

DsmccMessageHeader::~DsmccMessageHeader()
{

}