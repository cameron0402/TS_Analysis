#include "ParentalRatingDesc.h"

ParentalRatingDesc::RatingInfo::RatingInfo(uint8_t* data)
    : country_code(),
      rating(data[3])
{
    memcpy(country_code, data, 3);
}

ParentalRatingDesc::RatingInfo::~RatingInfo()
{
}

ParentalRatingDesc::ParentalRatingDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    RatingInfo* tmp;
    while(index < length + 2)
    {
        tmp = new RatingInfo(data + index);
        parent_rating_list.push_back(tmp);
        index += 4;
    }
}

ParentalRatingDesc::~ParentalRatingDesc()
{
    std::list<RatingInfo*>::iterator rit = parent_rating_list.begin();
    for(; rit != parent_rating_list.end(); ++rit)
        delete (*rit);
}

