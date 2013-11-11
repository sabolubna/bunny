#include "Button.h"

Button::Button() {}

Button::Button(ClickHandler* handler_, int x, int y, int w, int h) : posx_(x), posy_(y), width_(w), height_(h) {};

bool Button::clicked(int x, int y)
{
    if (x > posx_ && x < posx_ + width_ && y > posy_ && y < posy_ + height_)
        return true;
    return false;
}

void Button::draw(ALLEGRO_COLOR color)
{
    al_draw_filled_rectangle(posx_, posy_, posx_ + width_, posy_+height_, color);
}

void Button::onClick()
{
    handler_->onClick();
}

Button::~Button()
{
    //dtor
}
