#ifndef PICKUPFACTORY_H
#define PICKUPFACTORY_H

#include "Pickup.h"

class PickupFactory
{
    public:
        PickupFactory();
        ~PickupFactory();
        Pickup* create(RoomType type);
        Pickup* create(RoomType type, PickupType ptype);

    protected:
        ALLEGRO_BITMAP* numbers_, *pickups_;
};

#endif // PICKUPFACTORY_H
