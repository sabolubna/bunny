#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <vector>
#include "main.h"
#include "Level.h"
#include "Button.h"
#include "Menu.h"
#include "Panda.h"
#include "Room.h"

class Game
{
    public:
        Game();
        Game(int fp);
        ~Game();
        void play();

    private:
        ALLEGRO_EVENT_QUEUE *queue;
        Panda panda;
        vector<Element*> elements;
        int time;
        int date;
        int hp;
        int hearts;
        int state; //0 - levels, 1 - fight
        Menu pausemenu;
        //Room *currentroom;
        Level *currentlvl;
        Level levels[LVL_CNT];
        bool items[ITEM_CNT];
        float grades[GRADE_CNT]; // 0-failed, 1-nograde
        ALLEGRO_BITMAP *map, *itempics;

        void sort();
        void save();
        void screen();
        void fight();
        int pause();
        void timePass();
        void dayPass();
};

#endif // GAME_H
