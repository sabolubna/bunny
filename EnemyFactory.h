#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Enemy.h"

class EnemyFactory
{
    public:
        EnemyFactory(Bunny* bunny);
        ~EnemyFactory();
        Enemy* create();
        void setRange(int first, int last);

    protected:
        Bunny* bunny_;
        ALLEGRO_BITMAP *enemies_, *shots_;
        int firstEnemy_, lastEnemy_;
        bool allowedPos(Enemy* enemy);

    private:
};

#endif // ENEMYFACTORY_H
