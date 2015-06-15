#ifndef PARENTALRATINGDESC_H_HEADER_INCLUDED_AAA571BE
#define PARENTALRATINGDESC_H_HEADER_INCLUDED_AAA571BE
#include "../Descriptor.h"

//descriptor_tag = 0x55
//##ModelId=555AF96F0076
class ParentalRatingDesc : public Descriptor
{
  public:
    //##ModelId=555AF993010E
    class RatingInfo
    {
      public:
        //##ModelId=555AF9AE026E
        uint8_t country_code[3];
        //##ModelId=555AF9C700F7
        uint8_t rating;
    };

    //##ModelId=555AFA0F001E
    ParentalRatingDesc();

    //##ModelId=555AFA1C0387
    ParentalRatingDesc(uint8_t* data);

    //##ModelId=555AFA380210
    ~ParentalRatingDesc();

    //##ModelId=555AF9F20246
    std::list<RatingInfo> parent_rating_list;
};



#endif /* PARENTALRATINGDESC_H_HEADER_INCLUDED_AAA571BE */
