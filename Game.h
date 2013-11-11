#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <string>
#include <vector>
#include "main.h"
#include "ActualGame.h"
#include "Subgame.h"
#include "Menu.h"

class Game : public Delegate
{
    public:
        Game();
        ~Game();
        bool isRunning();
        void dispatchEvent(ALLEGRO_EVENT *event);
        void quit();

    private:
        bool running_;
        GameState state_;
        Subgame* subgame_;
        Menu* mainmenu_;
        Menu* pausemenu_;
        ActualGame* actualGame_;
};

#endif // GAME_H
