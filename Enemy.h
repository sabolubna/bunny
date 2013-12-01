#ifndef ENEMY_H
#define ENEMY_H

#include "Element.h"
#include "MovingStyle.h"
#include "ShootingStyle.h"
#include "Shot.h"
#include "Bunny.h"
#include <fstream>
#include <time.h>

using namespace std;

class Enemy : public Element
{
    public:
        Enemy(int x, int y, int type, ALLEGRO_BITMAP* enemies, ALLEGRO_BITMAP* shots, Bunny* bunny);
        ~Enemy();
        void dispatchEvent(ALLEGRO_EVENT* event);
        void bounceFromWall(int borders[4]);
        int handleCollision(Shot* shot);
        void draw();
        void move();
        vector<Shot*> shoot();
        double* getPos();
        int* getSize();

    protected:
        int animationState_;
        double animationTime_;
        double lastAnimation_;
        MovingStyle* movingStyle_;
        ShootingStyle* shootingStyle_;
        int hp_;
        double lastHurt_;

    private:
};

#endif // ENEMY_H
