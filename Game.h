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
        void play();
        void quit();
        void onPause();
        void resume();
        void endGame();
        void about();
        void back();
        void draw();

    private:
        bool running_;
        GameState state_;
        Subgame* subgame_;
        Menu* mainmenu_;
        Menu* pausemenu_;
        Menu* about_;
        ActualGame* actualGame_;
};

#endif // GAME_H
