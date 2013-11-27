#include "Button.h"

Button::Button() {}

Button::Button(ClickHandler* handler, int x, int y, int width, int height, int picposx, int picposy)
{
    handler_ = handler;
    posx_ = x;
    posy_ = y;
    width_ = width;
    height_ = height;
    ALLEGRO_BITMAP* buttons = al_load_bitmap("pics/buttons.png");
    picture_ = al_create_sub_bitmap(buttons, picposx, picposy, width, height);
}

bool Button::clicked(int x, int y)
{
    if (x > posx_ && x < posx_ + width_ && y > posy_ && y < posy_ + height_)
        return true;
    return false;
}

void Button::draw(ALLEGRO_COLOR color)
{
    al_draw_bitmap(picture_, posx_, posy_, 0);
}

void Button::onClick()
{
    handler_->onClick();
}

Button::~Button()
{
    //dtor
}
