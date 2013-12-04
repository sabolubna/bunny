#ifndef ITEM_H
#define ITEM_H

#include "Element.h"
#include "Bunny.h"
#include "RoomEffect.h"

class Item : public Element
{
    public:
        Item(int x, int y, int num, int price, ALLEGRO_BITMAP* items, ALLEGRO_BITMAP* numbers, ALLEGRO_BITMAP* shots_);
        ~Item();
        bool activate(Bunny* bunny, RoomEffect* room);
        void draw();
        bool handleCollision(Bunny* bunny, RoomEffect* room);
        bool pickUpSpaceItem(Bunny* bunny);
        bool lying();
        int price_;
        int number_;
        bool spaceItem_;

    protected:
        ALLEGRO_BITMAP* numbers_;
        ALLEGRO_BITMAP* shots_;
    private:
};

#endif // ITEM_H
