#ifndef SUBGAME_H
#define SUBGAME_H

#include <allegro5/allegro.h>
#include "Delegate.h"

class Subgame
{
    public:
        virtual void dispatchEvent(ALLEGRO_EVENT *event) = 0;
    protected:
        Delegate* delegate_;
};

#endif // SUBGAME_H
