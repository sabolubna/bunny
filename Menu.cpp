#include "Menu.h"


Menu::Menu(char bitmap[15], vector<Button> buttons)
{
    screen = al_load_bitmap(bitmap);
    buttons_ = buttons;
}

Menu::~Menu()
{
    //dtor
}

void Menu::dispatchEvent(ALLEGRO_EVENT *event)
{
    if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        int x, y;
        x = event->mouse.x;
        y = event->mouse.y;
        for (int i = 0; i < buttons_.size(); i++)
        {
            if (buttons_[i].clicked(x, y))
            {
                buttons_[i].onClick();
                return;
            }
        }
    }
}

void Menu::draw()
{
    al_draw_bitmap(screen, 0, 0, 0);
    for (int i = 0; i < buttons_.size(); i++)
    {
        buttons_[i].draw(al_map_rgb(255,255,255));
    }
    al_flip_display();
}
