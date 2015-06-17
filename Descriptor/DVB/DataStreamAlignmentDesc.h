#ifndef DATASTREAMALIGNMENTDESC_H_HEADER_INCLUDED_AAA7EDB3
#define DATASTREAMALIGNMENTDESC_H_HEADER_INCLUDED_AAA7EDB3
#include "../Descriptor.h"

//descriptor_tag = 0x06

//##ModelId=5558333201D6
class DataStreamAlignmentDesc : public Descriptor
{
  public:
    //##ModelId=5558335901A3
    DataStreamAlignmentDesc();

    //##ModelId=5558336A0265
    DataStreamAlignmentDesc(uint8_t* data);

    //##ModelId=555833A001F2
    virtual ~DataStreamAlignmentDesc();

    virtual void resolved();

    //##ModelId=555833B701CB
    uint8_t alignment_type;
};



#endif /* DATASTREAMALIGNMENTDESC_H_HEADER_INCLUDED_AAA7EDB3 */
