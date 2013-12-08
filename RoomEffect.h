#ifndef ROOMEFFECT_H
#define ROOMEFFECT_H

#include "main.h"

class RoomEffect
{
    public:
        virtual void newPickup(PickupType type) = 0;
        virtual void newPickup() = 0;
        virtual void oneRoomEffect(Effect effect, double change) = 0;

    protected:
    private:
};

#endif // ROOMEFFECT_H
