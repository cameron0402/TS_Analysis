#ifndef PARENTALRATINGDESC_H_HEADER_INCLUDED_AAA571BE
#define PARENTALRATINGDESC_H_HEADER_INCLUDED_AAA571BE
#include "../Descriptor.h"

//descriptor_tag = 0x55
class ParentalRatingDesc : public Descriptor
{
  public:
    class RatingInfo
    {
      public:
        RatingInfo(uint8_t* data);
        ~RatingInfo();
        uint8_t country_code[4];
        uint8_t rating;
    };

    ParentalRatingDesc(uint8_t* data);
    ~ParentalRatingDesc();
    std::list<RatingInfo*> parent_rating_list;
};



#endif /* PARENTALRATINGDESC_H_HEADER_INCLUDED_AAA571BE */
