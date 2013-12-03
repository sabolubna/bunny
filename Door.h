#ifndef DOOR_H
#define DOOR_H

#include "Element.h"
#include "main.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Door : public Element
{
    public:
        Door(Side side, RoomType type);
        Door(int num, RoomType type);
        ~Door();
        void bounceFromWall(int borders[4]);
        void unlock();
        void lock();
        bool fits(int posx, int posy, int width, int height);
        Side side_;
        bool locked_;
        bool keyNeeded_;
        void draw();

    protected:
        void init(Side side, RoomType type);
        RoomType type_;
        ALLEGRO_BITMAP* doorspic_;
};

#endif // DOOR_H
