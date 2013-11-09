#include "Menu.h"

Menu::Menu()
{

}

Menu::Menu(char bitmap[15], Button *butts, int cnt)
{
    butcnt = cnt;
    screen = al_load_bitmap(bitmap);
    buttons = butts;
}

Menu::~Menu()
{
    //dtor
}

void Menu::view()
{
    al_draw_bitmap(screen, 0, 0, 0);
    for (int i = 0; i < butcnt; i++)
    {
        buttons[i].draw(al_map_rgb(255,255,255));
    }
    al_flip_display();
}

int Menu::clicked(int x, int y)
{
    for (int i = 0; i < butcnt; i++)
    {
        if (buttons[i].clicked(x, y))
            return i;
    }
    return -1;
}
