#include "../Descriptor.h"
#include "DSMCCDescFactory.h"
#include "TypeDesc.h"
#include "NameDesc.h"
#include "InfoDesc.h"
#include "CRC32Desc.h"
#include "ModuleLinkDesc.h"
#include "LocationDesc.h"
#include "EstimatedDownloadTimeDesc.h"
#include "GroupLinkDesc.h"
#include "CompressModuleDesc.h"

Descriptor* DSMCCDescFactory::createDesc(uint8_t type, uint8_t* data)
{
    switch(type)
    {
        case 0x01: return new TypeDesc(data); 
        case 0x02: return new NameDesc(data);
        case 0x03: return new InfoDesc(data);
        case 0x04: return new ModuleLinkDesc(data);
        case 0x05: return new CRC32Desc(data);
        case 0x06: return new LocationDesc(data);
        case 0x07: return new EstimateDownloadTimeDesc(data);
        case 0x08: return new GroupLinkDesc(data);
        case 0x09: return new CompressModuleDesc(data);

        default:
            break;
    }

    return new Descriptor(data);
}