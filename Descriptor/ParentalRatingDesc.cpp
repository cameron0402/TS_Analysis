#include "ParentalRatingDesc.h"

//##ModelId=555AFA0F001E
ParentalRatingDesc::ParentalRatingDesc()
{
}

//##ModelId=555AFA1C0387
ParentalRatingDesc::ParentalRatingDesc(uint8_t* data) : Descriptor(data)
{
    int index = 2;
    RatingInfo tmp;
    while(index < length + 1)
    {
        memcpy(tmp.country_code, data + index, 3);
        tmp.rating = data[index + 4];
        parent_rating_list.push_back(tmp);
        index += 4;
    }
}

//##ModelId=555AFA380210
ParentalRatingDesc::~ParentalRatingDesc()
{
}

