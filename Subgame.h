#ifndef SUBGAME_H
#define SUBGAME_H

#include <allegro5/allegro.h>

class Subgame
{
    public:
        virtual void dispatchEvent(ALLEGRO_EVENT *event) = 0;
};

#endif // SUBGAME_H
