#ifndef CELLFREQUENCYLINKDESC_H_HEADER_INCLUDED_AAA2F6A4
#define CELLFREQUENCYLINKDESC_H_HEADER_INCLUDED_AAA2F6A4
#include "Descriptor.h"

// descriptor_tag = 0x6D
//##ModelId=555D368A008C
class CellFrequencyLinkDesc : public Descriptor
{
  public:
    //##ModelId=555D36F500D5
    class FreqInfo
    {
      public:
        //##ModelId=555D375A0054
        class FreqExInfo
        {
          public:
            //##ModelId=555D376F01BC
            uint8_t cell_id_extension;
            //##ModelId=555D378401EE
            uint32_t transposer_frequency;
        };

        //##ModelId=555D370A0067
        uint16_t cell_id;
        //##ModelId=555D371A0245
        uint32_t frequency;
        //##ModelId=555D373D0222
        uint8_t subcell_info_loo_length;
        //##ModelId=555D3752029E
        std::list<FreqExInfo> ex_list;
    };

    //##ModelId=555D36A70015
    CellFrequencyLinkDesc();

    //##ModelId=555D36AF01DD
    CellFrequencyLinkDesc(uint8_t* data);

    //##ModelId=555D36B102A9
    virtual ~CellFrequencyLinkDesc();

    //##ModelId=555D37C40220
    std::list<FreqInfo> freq_list;
};



#endif /* CELLFREQUENCYLINKDESC_H_HEADER_INCLUDED_AAA2F6A4 */
