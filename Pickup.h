#ifndef PICKUP_H
#define PICKUP_H

#include "Element.h"


class Pickup : public Element
{
    public:
        Pickup(int x, int y, int type, int price, ALLEGRO_BITMAP* pickups, ALLEGRO_BITMAP* numbers);
        ~Pickup();
        void draw();
        int price_ ;
        int type_;

    protected:
        ALLEGRO_BITMAP* numbers_;

    private:
};

#endif // PICKUP_H
