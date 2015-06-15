#ifndef ESTIMATE_DOWNLOAD_TIME_DESC_H_
#define ESTIMATE_DOWNLOAD_TIME_DESC_H_

#include "../Descriptor.h"
//descriptor_tag = 0x07

class EstimateDownloadTimeDesc : public Descriptor
{
public:
    EstimateDownloadTimeDesc();
    EstimateDownloadTimeDesc(uint8_t* data);
    virtual ~EstimateDownloadTimeDesc();

    uint32_t estimate_download_time;
};


#endif