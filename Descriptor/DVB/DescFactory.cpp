#include "../Descriptor.h"
#include "DescFactory.h"
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
#include "CellListDesc.h"
#include "CellFrequencyLinkDesc.h"
#include "AnnouncementSupportDesc.h"
#include "AdaptationFieldDataDesc.h"
#include "S2SatelliteDeliverySystemDesc.h"
#include "DTSAudioStreamDesc.h"
#include "AACDesc.h"
#include "ExtensionDesc.h"
#include "AssociationTagDesc.h"
#include "CarouselIdentifierDesc.h"
#include "LogicalChannelDesc.h"

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

        //descriptors used in DSM-CC
        case 0x13: return new CarouselIdentifierDesc(data);
        case 0x14: return new AssociationTagDesc(data);

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
        case 0x6C: return new CellListDesc(data);
        case 0x6D: return new CellFrequencyLinkDesc(data);
        case 0x6E: return new AnnouncementSupportDesc(data);
        case 0x70: return new AdaptationFieldDataDesc(data);
        case 0x79: return new S2SatelliteDeliverySystemDesc(data);
        case 0x7B: return new DTSAudioStreamDesc(data);
        case 0x7C: return new AACDesc(data);
        case 0x7F: return new ExtensionDesc(data);

        //
        case 0x83: return new LogicalChannelDesc(data);
  
        //descriptors that can't find definitions
        case 0x6F: //Application_signalling_descriptor
        case 0x71: //Service_identifier_descriptor
        case 0x72: //Service_availability_descriptor
        case 0x73: //default_authority_descriptor
        case 0x74: //related_content_descriptor
        case 0x75: //TVA_id_descriptor
        case 0x76: //content_identifier_descriptor
        case 0x77: //time_slice_fec_identifier_descriptor
        case 0x78: //ECM_repetition_rate_descriptor
        case 0x7A: //enhanced_AC-3_descriptor

        //ATSC descriptors, user private, also can't find definitions
        case 0x81: //AC3_audio_descriptor
        case 0x82: //SCTE Frame_rate_descriptor
        case 0x84: //SCTE Component_name_descriptor
        case 0x85: //ATSC program_identifier
        case 0x86: //Caption_service_descriptor
        case 0x87: //Content_advisory_descriptor
        case 0x88: //ATSC CA_descriptor
        case 0x93: //SCTE Revision detection descriptor
        case 0xA3: //component_name_descriptor
        case 0xAA: //ATSC rc_descriptor

        default: 
            break;
    }

    return new Descriptor(data);
}

