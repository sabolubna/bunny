#ifndef Bunny_H
#define Bunny_H

#include <string>
#include "Element.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include "Door.h"
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
        int damage_;
        ALLEGRO_BITMAP *shotPicture_;
        double range_;
        double animationTime_;
        double shotTime_;
        int spaceItem_;
        ALLEGRO_BITMAP* spacePicture_;

    protected:
        double lastAnimation_;
        int jumpState_;
        double lastShot_;
        ALLEGRO_BITMAP* shots_;
        Side shotDirection_;
        bool shooting_;
        double immunityTime_;

    private:
};

#endif // Bunny_H
