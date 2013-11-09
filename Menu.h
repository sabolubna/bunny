#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Button.h"

class Menu
{
    public:
        Menu();
        Menu(char bitmap[15], Button *butts, int cnt);
        ~Menu();
        void view();
        int clicked(int x, int y);

    private:
        Button *buttons;
        int butcnt;
        ALLEGRO_BITMAP *screen, *instr;
};

#endif // MENU_H
