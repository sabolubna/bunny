#ifndef Bunny_H
#define Bunny_H

#include "Element.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <time.h>
#include <typeinfo>
#include "Door.h"
#include "Item.h"

class Bunny : public Element
{
    public:
        Bunny();
        ~Bunny();
        void setPos(int x, int y, int z);
        void draw();
        void dispatchEvent(ALLEGRO_EVENT* event);
        int atDoor_;
        void handleCollision(Door* door);
        int handleCollision(Item* item);
        int keys_;
        int bombs_;
        int coins_;
        int hearts_;
        int hp_;
        bool itemsCollected[ITEM_CNT];

    protected:
        double lastAnimation_;
        double animationTime_;
        int jumpState_;

    private:
};

#endif // Bunny_H
