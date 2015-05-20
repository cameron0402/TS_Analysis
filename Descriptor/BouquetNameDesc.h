#ifndef BOUQUETNAMEDESC_H_HEADER_INCLUDED_AAA50D34
#define BOUQUETNAMEDESC_H_HEADER_INCLUDED_AAA50D34
#include "Descriptor.h"

//descriptor_tag = 0x47
//##ModelId=555A8C81038D
class BouquetNameDesc : public Descriptor
{
  public:
    //##ModelId=555A8CC90092
    BouquetNameDesc();

    //##ModelId=555A8CE10380
    BouquetNameDesc(uint8_t* data);

    //##ModelId=555A8CFB0209
    virtual ~BouquetNameDesc();

    //##ModelId=555A8CA202F0
    uint8_t* bouquet_name;
};



#endif /* BOUQUETNAMEDESC_H_HEADER_INCLUDED_AAA50D34 */
