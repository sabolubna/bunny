#ifndef ACTUALGAME_H
#define ACTUALGAME_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "main.h"
#include <vector>
#include "Bunny.h"
#include "Element.h"
#include "Level.h"
#include "Room.h"
#include "Subgame.h"

class ActualGame : public Subgame
{
    public:
        ActualGame(Delegate* delegate);
        ~ActualGame();
        void dispatchEvent(ALLEGRO_EVENT *event);
        void nextLevel();
        void draw();

    protected:
        Delegate* delegate_;
        Level* level_;
        bool usedlevels_[LEVELTYPES];
    private:
};

#endif // ACTUALGAME_H
