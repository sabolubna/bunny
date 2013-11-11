#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <vector>
#include "Button.h"
#include "Subgame.h"
#include "Delegate.h"

using namespace std;

class Menu : public Subgame
{
    public:
        Menu(char bitmap[15], vector<Button> buttons);
        ~Menu();
        void draw();
        int clicked(int x, int y);
        void dispatchEvent(ALLEGRO_EVENT *event);

    private:
        vector<Button> buttons_;
        ALLEGRO_BITMAP *screen;
};

#endif // MENU_H
