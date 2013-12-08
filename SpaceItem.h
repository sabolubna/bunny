#ifndef SPACEITEM_H
#define SPACEITEM_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "RoomEffect.h"
#include "Bunny.h"

class SpaceItem
{
    public:
        SpaceItem(ALLEGRO_BITMAP* picture, int num);
        ~SpaceItem();
        void draw();
        void onSpace(RoomEffect* room, Bunny* bunny);
        ALLEGRO_BITMAP* picture_;
        int number_;
        int roomsLeft_;

    protected:
        ALLEGRO_BITMAP* numbers_;
    private:
};

#endif // SPACEITEM_H
