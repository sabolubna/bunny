#ifndef ENEMY_H
#define ENEMY_H

#include "Element.h"
#include "MovingStyle.h"
#include "ShootingStyle.h"
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
        void draw();
        void move();
        vector<Shot*> shoot();
        void freeze();
        bool hurt(int damage);
        double* getSpeed();

    protected:
        int animationState_;
        double animationTime_;
        double lastAnimation_;
        MovingStyle* movingStyle_;
        ShootingStyle* shootingStyle_;
        int hp_;
        double lastHurt_;
        int stateCount_;

    private:
};

#endif // ENEMY_H
