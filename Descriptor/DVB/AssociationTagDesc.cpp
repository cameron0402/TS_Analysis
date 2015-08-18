#include "AssociationTagDesc.h"

AssociationTagDesc::AssociationTagDesc(uint8_t* data)
    : Descriptor(data),
      association_tag((data[2] << 8) | data[3]),
      use((data[4] << 8) | data[5]),
      selector_length(data[6])
{
    if(use == 0x00)
    {
        transaction_id = (data[7] << 24) | (data[8] << 16) | (data[9] << 8) | data[10];
        time_out = (data[11] << 24) | (data[12] << 16) | (data[13] << 8) | data[14];
    }
}

AssociationTagDesc::~AssociationTagDesc()
{

}