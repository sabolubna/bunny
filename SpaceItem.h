#ifndef SPACEITEM_H
#define SPACEITEM_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
class Bunny;

class SpaceItem
{
    public:
        SpaceItem(ALLEGRO_BITMAP* picture, int num);
        ~SpaceItem();
        void draw();
        void onSpace(Bunny* bunny);
        ALLEGRO_BITMAP* picture_;
        int number_;
        int roomsLeft_;

    protected:
    private:
};

#endif // SPACEITEM_H
