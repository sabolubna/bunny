#ifndef Bunny_H
#define Bunny_H

#include <string>
#include "Element.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include "Door.h"
#include "Item.h"
#include "Shot.h"
#include "Pickup.h"

class Bunny : public Element
{
    public:
        Bunny();
        ~Bunny();
        void draw();
        void dispatchEvent(ALLEGRO_EVENT* event);
        void handleCollision(Door* door);
        int handleCollision(Item* item);
        int handleCollision(Pickup* pickup);
        void hurt(int damage);
        bool alive();
        int keys_;
        int atDoor_;
        bool atPortal_;
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
        ALLEGRO_BITMAP* shots_, *shotPicture_;
        double range_;
        int damage_;
        Side shotDirection_;
        bool shooting_;
        double immunityTime_;

    private:
};

#endif // Bunny_H
