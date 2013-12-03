#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "Item.h"
#include "Bunny.h"
#include "main.h"

class ItemFactory
{
    public:
        ItemFactory(Bunny* bunny);
        ~ItemFactory();
        Item* create(RoomType type);
        void setRange(int first, int last);

    protected:
        int firstItem_, lastItem_;
        ALLEGRO_BITMAP* numbers_, *items_;
        Bunny* bunny_;
};

#endif // ITEMFACTORY_H
