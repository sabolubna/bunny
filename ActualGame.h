#ifndef ACTUALGAME_H
#define ACTUALGAME_H

class Game;

#include "main.h"
#include <vector>
#include "Panda.h"
#include "Element.h"
#include "Menu.h"
#include "Level.h"

class ActualGame : public Subgame
{
    public:
        ActualGame();
        ~ActualGame();
    protected:
        void dispatchEvent(Game* game, ALLEGRO_EVENT *event);
        Panda panda;
        vector<Element*> elements;
        GameState state;
        //Room *currentroom;
        Level *currentlvl;
        Level levels[LVL_CNT];
        bool items[ITEM_CNT];
        ALLEGRO_BITMAP *itempics;

        void sort();
        void save();
        void screen();
        void fight();
        int pause();
    private:
};

#endif // ACTUALGAME_H
