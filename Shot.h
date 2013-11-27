#ifndef SHOT_H
#define SHOT_H

#include "Element.h"
#include <Math.h>


class Shot : public Element
{
    public:
        Shot(ALLEGRO_BITMAP *pic, int posx, int posy, int posz, double speedx, double speedy,
             double range, bool hurtsBunny, int dmg);
        ~Shot();
        void move();
        void bounceFromWall(int borders[4]);
        double range_;
        bool hurtsBunny_;
        int damage_;

    protected:

    private:
};

#endif // SHOT_H
