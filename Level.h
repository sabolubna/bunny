#ifndef LEVEL_H
#define LEVEL_H

#include "main.h"
#include "Room.h"
#include "EnemyFactory.h"
#include "ItemFactory.h"
#include "PickupFactory.h"
#include <string>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Level
{
    friend class ActualGame;
    public:
        Level();
        ~Level();
        void dispatchEvent(ALLEGRO_EVENT* event);
        void enter(Room* room);
        void draw();
        void nextLevel();
        Room* currentRoom_;

    protected:
        ALLEGRO_BITMAP *background_, *numbers_, *hearts_;
        Room* firstRoom_;
        Bunny* bunny_;
        EnemyFactory* efactory_;
        ItemFactory* ifactory_;
        PickupFactory* pfactory_;
        bool usedLevels_[LVL_CNT];
        int levelsPlayed_;
        bool playing_;

    private:
};

#endif // LEVEL_H
