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
    if (type == SHOP)
    {
        return new Pickup(428, 308, rand()%4, rand()%3+1, pickups_, numbers_);
    }
    else
        return new Pickup(rand()%665 + 50, rand()%415 + 135, rand()%4, 0, pickups_, numbers_);
}

Pickup* PickupFactory::create(RoomType type, PickupType ptype)
{
    return new Pickup(rand()%665 + 50, rand()%450 + 135, ptype, 0, pickups_, numbers_);
}
