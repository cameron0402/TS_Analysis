#include "DescFactory.h"
#include "Descriptor.h"
#include "VideoSTreamDesc.h"
#include "AudioStreamDesc.h"
#include "HierarchyDesc.h"
#include "RegistrationDesc.h"
#include "DataStreamAlignmentDesc.h"
#include "TargetBackgroundGridDesc.h"
#include "VideoWindowDesc.h"
#include "CADesc.h"
#include "ISO639LanguageDesc.h"
#include "SystemClockDesc.h"
#include "MultiplexBufferUtilizationDesc.h"
#include "CopyrightDesc.h"
#include "MaximumBitrateDesc.h"
#include "PrivateDataIndicatorDesc.h"
#include "SmoothingBufferDesc.h"
#include "STDDesc.h"
#include "IBPDesc.h"
#include "NetworkNameDesc.h"
#include "ServiceListDesc.h"
#include "StuffingDesc.h"
#include "SatelliteDeliverySystemDesc.h"
#include "CableDeliverySystemDesc.h"
#include "VBIDataDesc.h"
#include "VBITeletextDesc.h"
#include "BouquetNameDesc.h"
#include "ServiceDesc.h"
#include "CountryAvailabilityDesc.h"
#include "LinkageDesc.h"
#include "NVODReferenceDesc.h"
#include "TimeShiftedServiceDesc.h"
#include "ShortEventDesc.h"
#include "ExtendedEventDesc.h"
#include "TimeShiftedEventDesc.h"
#include "ComponentDesc.h"
#include "MosaicDesc.h"
#include "StreamIdentifierDesc.h"
#include "CAIdentifierDesc.h"
#include "ContentDesc.h"
#include "ParentalRatingDesc.h"
#include "TeletextDesc.h"
#include "TelephoneDesc.h"
#include "LocalTimeOffsetDesc.h"
#include "SubtitlingDesc.h"
#include "TerrestrialDeliverySystemDesc.h"
#include "MultilingualNetworkNameDesc.h"
#include "MultilingualBouquetNameDesc.h"
#include "MultilingualServiceNameDesc.h"
#include "MultilingualComponentDesc.h"
#include "PrivateDataSpecifierDesc.h"
#include "ServiceMoveDesc.h"
#include "ShortSmoothingBufferDesc.h"
#include "FrequencyListDesc.h"
#include "PartialTransportStreamDesc.h"
#include "DataBroadcastDesc.h"
#include "DataBroadcastIDDesc.h"
#include "PDCDesc.h"
#include "AC3Desc.h"
#include "AncillaryDataDesc.h"
#include "AnnouncementSupportDesc.h"

//##ModelId=55585690038B
Descriptor* DescFactory::createDesc(uint8_t type, uint8_t* data)
{
    switch(type)
    {
        //service descriptors
        case 0x02: return new VideoStreamDesc(data);
        case 0x03: return new AudioStreamDesc(data);
        case 0x04: return new HierarchyDesc(data);
        case 0x05: return new RegistrationDesc(data);
        case 0x06: return new DataStreamAlignmentDesc(data);
        case 0x07: return new TargetBackgroundGridDesc(data);
        case 0x08: return new VideoWindowDesc(data);
        case 0x09: return new CADesc(data);
        case 0x0A: return new ISO639LanguageDesc(data);
        case 0x0B: return new SystemClockDesc(data);
        case 0x0C: return new MultiplexBufferUtilizationDesc(data);
        case 0x0D: return new CopyrightDesc(data);
        case 0x0E: return new MaximumBitrateDesc(data);
        case 0x0F: return new PrivateDataIndicatorDesc(data);
        case 0x10: return new SmoothingBufferDesc(data);
        case 0x11: return new STDDesc(data);
        case 0x12: return new IBPDesc(data);

        //dvb descriptors
        case 0x40: return new NetworkNameDesc(data);
        case 0x41: return new ServiceListDesc(data);
        case 0x42: return new StuffingDesc(data);
        case 0x43: return new SatelliteDeliverySystemDesc(data);
        case 0x44: return new CableDeliverySystemDesc(data);
        case 0x45: return new VBIDataDesc(data);
        case 0x46: return new VBITeletextDesc(data);
        case 0x47: return new BouquetNameDesc(data);
        case 0x48: return new ServiceDesc(data);
        case 0x49: return new CountryAvailabilityDesc(data);
        case 0x4A: return new LinkageDesc(data);
        case 0x4B: return new NVODReferenceDesc(data);
        case 0x4C: return new TimeShiftedServiceDesc(data);
        case 0x4D: return new ShortEventDesc(data);
        case 0x4E: return new ExtendedEventDesc(data);
        case 0x4F: return new TimeShiftedEventDesc(data);
        case 0x50: return new ComponentDesc(data);
        case 0x51: return new MosaicDesc(data);
        case 0x52: return new StreamIdentifierDesc(data);
        case 0x53: return new CAIdentifierDesc(data);
        case 0x54: return new ContentDesc(data);
        case 0x55: return new ParentalRatingDesc(data);
        case 0x56: return new TeletextDesc(data);
        case 0x57: return new TelephoneDesc(data);
        case 0x58: return new LocalTimeOffsetDesc(data);
        case 0x59: return new SubtitlingDesc(data);
        case 0x5A: return new TerrestrialDeliverySystemDesc(data);
        case 0x5B: return new MultilingualNetworkNameDesc(data);
        case 0x5C: return new MultilingualBouquetNameDesc(data);
        case 0x5D: return new MultilingualServiceNameDesc(data);
        case 0x5E: return new MultilingualComponentDesc(data);
        case 0x5F: return new PrivateDataSpecifierDesc(data);
        case 0x60: return new ServiceMoveDesc(data);
        case 0x61: return new ShortSmoothingBufferDesc(data);
        case 0x62: return new FrequencyListDesc(data);
        case 0x63: return new PartialTransportStreamDesc(data);
        case 0x64: return new DataBroadcastDesc(data);
        case 0x66: return new DataBroadcastIDDesc(data);
        case 0x69: return new PDCDesc(data);
        case 0x6A: return new AC3Desc(data);
        case 0x6B: return new AncillaryDataDesc(data);
        case 0x6E: return new AnnouncementSupportDesc(data);
        default: break;
    }

    return NULL;
}

