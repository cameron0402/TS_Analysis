#ifndef _DSMCC_MESSAGE_HEADER_H_
#define _DSMCC_MESSAGE_HEADER_H_

#include "../../def.h"

class DsmccMessageHeader
{
public:

    DsmccMessageHeader();
    DsmccMessageHeader(uint8_t* data);
    virtual ~DsmccMessageHeader();

    uint8_t protocol_discriminator;
    uint8_t dsmcc_type;
    uint16_t messageId;
    uint32_t transactionId; //downloadID
    uint8_t adaptation_length;
    uint16_t message_length;

    bool operator<(const DsmccMessageHeader& dsmh);
    bool operator==(const DsmccMessageHeader& dsmh);
    //adaptation_header ingored
};

typedef DsmccMessageHeader DsmccDownloadDataHeader;

#endif