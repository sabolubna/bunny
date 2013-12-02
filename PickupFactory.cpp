#include "PickupFactory.h"

PickupFactory::PickupFactory()
{
    numbers_ = al_load_bitmap("pics/numbers.bmp");
    al_convert_mask_to_alpha(numbers_, al_map_rgb(0, 0, 0));

    pickups_ = al_load_bitmap("pics/pickups.png");
    al_convert_mask_to_alpha(pickups_, al_map_rgb(255, 255, 255));
}

PickupFactory::~PickupFactory()
{
    //dtor
}

Pickup* PickupFactory::create(RoomType type)
{
    return new Pickup(rand()%665 + 50, rand()%450 + 135, rand()%4, 0, pickups_, numbers_);
}
