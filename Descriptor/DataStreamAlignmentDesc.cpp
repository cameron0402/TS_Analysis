#include "DataStreamAlignmentDesc.h"

//##ModelId=5558335901A3
DataStreamAlignmentDesc::DataStreamAlignmentDesc()
{
}

//##ModelId=5558336A0265
DataStreamAlignmentDesc::DataStreamAlignmentDesc(uint8_t* data) 
    : Descriptor(data),
      alignment_type(data[2])
{
}

//##ModelId=555833A001F2
DataStreamAlignmentDesc::~DataStreamAlignmentDesc()
{
}

void DataStreamAlignmentDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("data_stream_alignment_descriptor");

    sprintf(arr, "0x%x", alignment_type);
    tmp = new TiXmlElement("alignment_type");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);
}

