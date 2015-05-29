#include "DataBroadcastIDDesc.h"

//##ModelId=555C416100DA
DataBroadcastIDDesc::DataBroadcastIDDesc()
{
}

//##ModelId=555C416300C2
DataBroadcastIDDesc::DataBroadcastIDDesc(uint8_t* data)
    : Descriptor(data),
      data_broadcast_id((data[2] << 8) | data[3])
{
    id_selector = new uint8_t[length - 2];
    memcpy(id_selector, data + 4, length - 2);
}

//##ModelId=555C4166014A
DataBroadcastIDDesc::~DataBroadcastIDDesc()
{
    delete []id_selector;
}

void DataBroadcastIDDesc::resolved()
{
    TiXmlElement* tmp;
    char arr[16] = {0};

    Descriptor::resolved();
    xml->SetValue("data_broadcast_id_descriptor");

    sprintf(arr, "0x%x", data_broadcast_id);
    tmp = new TiXmlElement("data_broadcast_id");
    tmp->LinkEndChild(new TiXmlText(arr));
    xml->LinkEndChild(tmp);
}

