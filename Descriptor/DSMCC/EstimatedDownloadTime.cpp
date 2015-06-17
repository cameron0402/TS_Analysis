#include "EstimatedDownloadTimeDesc.h"

EstimateDownloadTimeDesc::EstimateDownloadTimeDesc()
{

}

EstimateDownloadTimeDesc::EstimateDownloadTimeDesc(uint8_t* data)
    : Descriptor(data),
      estimate_download_time((data[2] << 24) | (data[3] << 16) | (data[4] << 8) | data[5])
{

}

EstimateDownloadTimeDesc::~EstimateDownloadTimeDesc()
{

}