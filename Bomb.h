#ifndef BOMB_H
#define BOMB_H

#include "Element.h"

class Bomb : public Element
{
    public:
        Bomb(double* bunnyPos);
        ~Bomb();
        void draw();
        void dispatchEvent(ALLEGRO_EVENT* event);
        bool smoke();
        bool exploded_;
        bool inRange(Element* element);
        int damage_;

    protected:
        double explosionTime_;
        int state_;
        int color_;
};

#endif // BOMB_H
