#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(int first, int last, Bunny* bunny)
{
    bunny_ = bunny;

    shots_ = al_load_bitmap("pics/shots.png");
    al_convert_mask_to_alpha(shots_, al_map_rgb(255, 255, 255));

    enemies_ = al_load_bitmap("pics/enemies.png");
    al_convert_mask_to_alpha(enemies_, al_map_rgb(255, 255, 255));
    setRange(first, last);
}

EnemyFactory::~EnemyFactory()
{
    //dtor
}

void EnemyFactory::setRange(int first, int last)
{
    firstEnemy_ = first;
    lastEnemy_ = last;
}

bool EnemyFactory::allowedPos(Enemy* enemy)
{
    double* enemyPos = enemy->getPos();
    int* enemySize = enemy->getSize();
    double posx = enemyPos[0];
    double posy = enemyPos[1];
    Element elements[4];
    elements[0].setPos(50, 365, 0);
    elements[1].setPos(670, 365, 0);
    elements[2].setPos(360, 180, 0);
    elements[3].setPos(360, 550, 0);
    int width = enemySize[0];
    int height = enemySize[1];
    int borders[] = {50, 100, 750, 550};
    if (posx + width > borders[RIGHT])
        return false;
    if (posy - height < borders[UP])
        return false;
    for (int i = 0; i < 4; i++)
    {
        if (enemy->collidesWith(&elements[i]))
            return false;
    }
    return true;
}

Enemy* EnemyFactory::create()
{
    Enemy* enemy = new Enemy(rand()%700+50, rand()%450+100, rand()%(lastEnemy_ - firstEnemy_ + 1) + firstEnemy_,
                             enemies_, shots_, bunny_);
    while (!allowedPos(enemy))
    {
        int x = rand()%700+50;
        int y = rand()%450+100;
        enemy->setPos(x, y, 20);
    }
    return enemy;
}
