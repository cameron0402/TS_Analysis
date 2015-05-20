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

