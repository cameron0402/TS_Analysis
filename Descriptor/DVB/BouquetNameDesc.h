#ifndef BOUQUETNAMEDESC_H_HEADER_INCLUDED_AAA50D34
#define BOUQUETNAMEDESC_H_HEADER_INCLUDED_AAA50D34
#include "../Descriptor.h"

//descriptor_tag = 0x47
class BouquetNameDesc : public Descriptor
{
  public:
    BouquetNameDesc(uint8_t* data);
    virtual ~BouquetNameDesc();
    uint8_t* bouquet_name;
};



#endif /* BOUQUETNAMEDESC_H_HEADER_INCLUDED_AAA50D34 */
