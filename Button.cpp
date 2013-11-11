#include "Button.h"

Button::Button() {}

Button::Button(Delegate* delegate, int x, int y, int w, int h) : posx(x), posy(y), width(w), height(h) {}

bool Button::clicked(int x, int y)
{
    if (x > posx && x < posx + width && y > posy && y < posy + height)
        return true;
    return false;
}

void Button::draw(ALLEGRO_COLOR color)
{
    al_draw_filled_rectangle(posx, posy, posx + width, posy+height, color);
}

Button::~Button()
{
    //dtor
}
