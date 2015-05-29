#include "AudioStreamDesc.h"

//##ModelId=55582BF20091
AudioStreamDesc::AudioStreamDesc()
{
}

//##ModelId=55582C000312
AudioStreamDesc::AudioStreamDesc(uint8_t* data) 
    : Descriptor(data), 
      free_format_flag(data[2] >> 7),
      ID((data[2] >> 6) & 0x01), 
      layer((data[2] >> 4) & 0x03), 
      variable_rate_audio_indicator((data[2] >> 3) & 0x01)
{
}

//##ModelId=55582C65023A
AudioStreamDesc::~AudioStreamDesc()
{
}

void AudioStreamDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("audio_stream_descriptor");

    sprintf(arr, "0x%x", free_format_flag);
    tmp = new TiXmlElement("free_format_flag");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", ID);
    tmp = new TiXmlElement("ID");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", layer);
    tmp = new TiXmlElement("layer");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", variable_rate_audio_indicator);
    tmp = new TiXmlElement("variable_rate_audio_indicator");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);
}

