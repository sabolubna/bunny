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
#include "Shot.h"
#include "Pickup.h"

class Bunny : public Element
{
    public:
        Bunny(ALLEGRO_BITMAP* shots);
        ~Bunny();
        void setPos(int x, int y, int z);
        void draw();
        void dispatchEvent(ALLEGRO_EVENT* event);
        int atDoor_;
        void handleCollision(Door* door);
        int handleCollision(Item* item);
        void handleCollision(Shot* shot);
        int handleCollision(Pickup* pickup);
        int keys_;
        int bombs_;
        int coins_;
        int hearts_;
        int hp_;
        bool itemsCollected[ITEM_CNT];
        Shot* shoot();

    protected:
        double lastAnimation_;
        double animationTime_;
        int jumpState_;
        double shotTime_;
        double lastShot_;
        ALLEGRO_BITMAP* shotPicture_;
        double range_;
        int damage_;
        Side shotDirection_;
        bool shooting_;

    private:
};

#endif // Bunny_H
