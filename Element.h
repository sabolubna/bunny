#ifndef ELEMENT_H
#define ELEMENT_H

#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <Math.h>

#include "Room.h"

class Element
{
    public:
        Element();
        virtual ~Element();
        virtual void draw();
        int compareTo(Element that);
        bool collides(Element that);
        void changeSpeed(int x, int y);
        void setSpeed(int x, int y);
        void move();
        void wall(Room* room);

    protected:
        double posx, posy, posz;
        double height, width, length;
        ALLEGRO_BITMAP *picture;
        double step;
        int speedx, speedy;

    private:
};

#endif // ELEMENT_H
