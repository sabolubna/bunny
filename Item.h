#ifndef ITEM_H
#define ITEM_H

#include "Element.h"


class Item : public Element
{
    public:
        Item(int x, int y, int num, int price);
        ~Item();
        int price_;
        int number_;
        bool spaceItem_;
        void activate();
        void draw();

    protected:

    private:
};

#endif // ITEM_H
