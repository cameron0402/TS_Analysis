#include "VideoStreamDesc.h"

//##ModelId=55582A460309
VideoStreamDesc::VideoStreamDesc()
{
}

//##ModelId=55582A5201C9
VideoStreamDesc::VideoStreamDesc(uint8_t* data) 
    : Descriptor(data),
      multiple_frame_rate_flag(data[2] >> 7),
      frame_rate_code((data[2] >> 3) & 0x0F),
      MPEG_1_only_flag((data[2] >> 2) & 0x01),
      constrained_parameter_flag((data[2] >> 1) & 0x01),
      still_picture_flag(data[2] & 0x01)
{
    if(!MPEG_1_only_flag)
    {
        profile_and_level_indication = data[3];
        chroma_format = data[4] >> 6;
        frame_rate_extension_flag = (data[4] >> 5) & 0x01;
    }
}

//##ModelId=55582A8C0059
VideoStreamDesc::~VideoStreamDesc()
{
}

void VideoStreamDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("video_stream_descriptor");

    sprintf(arr, "0x%x", multiple_frame_rate_flag);
    tmp = new TiXmlElement("multiple_frame_rate_flag");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", frame_rate_code);
    tmp = new TiXmlElement("frame_rate_code");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", MPEG_1_only_flag);
    tmp = new TiXmlElement("MPEG_1_only_flag");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", constrained_parameter_flag);
    tmp = new TiXmlElement("constrained_parameter_flag");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    sprintf(arr, "0x%x", still_picture_flag);
    tmp = new TiXmlElement("still_picture_flag");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);

    if(!MPEG_1_only_flag)
    {
        sprintf(arr, "0x%x", profile_and_level_indication);
        tmp = new TiXmlElement("profile_and_level_indication");
        tmp->LinkEndChild(new TiXmlText(arr));
        xml->LinkEndChild(tmp);

        sprintf(arr, "0x%x", chroma_format);
        tmp = new TiXmlElement("chroma_format");
        tmp->LinkEndChild(new TiXmlText(arr));
        xml->LinkEndChild(tmp);

        sprintf(arr, "0x%x", frame_rate_extension_flag);
        tmp = new TiXmlElement("frame_rate_extension_flag");
        tmp->LinkEndChild(new TiXmlText(arr));
        xml->LinkEndChild(tmp);
    }
}

