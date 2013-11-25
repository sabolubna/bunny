#ifndef ELEMENT_H
#define ELEMENT_H

#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <Math.h>

using namespace std;

class Element
{
    public:
        virtual ~Element();
        virtual void draw();
        virtual void dispatchEvent(ALLEGRO_EVENT* event);
        void changeSpeedBy(int x, int y);
        void setSpeed(int x, int y);
        virtual void move();
        bool collidesWith(Element* that);
        virtual void bounceFromWall(int borders[4]);
        bool lessThan(Element* that);
        double posy_;

    protected:
        double posx_, posz_;
        double pic_height_, pic_width_, height_, width_;
        ALLEGRO_BITMAP *picture_;
        double step_;
        int speedx_, speedy_;

    private:
};

#endif // ELEMENT_H
