#ifndef LEVEL_H
#define LEVEL_H

#include "main.h"
#include "Room.h"
#include <string>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Level
{
    friend class ActualGame;
    public:
        Level(int levelnum, Bunny* bunny);
        ~Level();
        void dispatchEvent(ALLEGRO_EVENT* event);
        void enter(Room* room);
        void draw();

    protected:
        ALLEGRO_BITMAP *background_, *numbers_, *hearts_;
        Room* firstRoom_;
        Room* currentRoom_;
        Bunny* bunny_;

    private:
};

#endif // LEVEL_H
