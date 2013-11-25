#include "Element.h"

Element::~Element()
{
    //dtor
}

void Element::dispatchEvent(ALLEGRO_EVENT* event)
{

}

bool Element::lessThan(Element* that)
{
    return posy_ < that->posy_;
}

void Element::bounceFromWall(int borders[4])
{
    if (posx_ < borders[LEFT])
        posx_ = borders[LEFT] + 1;
    if (posx_ + width_ > borders[RIGHT])
        posx_ = borders[RIGHT] - 1 - width_;
    if (posy_ > borders[DOWN])
        posy_ = borders[DOWN] - 1;
    if (posy_ - height_ < borders[UP])
        posy_ = borders[UP] + 1 + height_;
}

void Element::changeSpeedBy(int x, int y)
{
    speedx_ += x;
    speedy_ += y;
}

void Element::setSpeed(int x, int y)
{
    speedx_ = x;
    speedy_ = y;
}

void Element::move()
{
    if (speedx_ == 0 && speedy_ == 0) return;
    double sq = sqrt(pow(speedx_,2)+pow(speedy_,2));
    posx_ += 1.0 * speedx_ * step_ / sq;
    posy_ += 1.0 * speedy_ * step_ / sq;
}

void Element::draw()
{
    al_draw_bitmap(picture_, posx_, posy_ - pic_height_ - posz_, 0);
}

bool Element::collidesWith(Element* that)
{
    return (posx_ + width_ > that->posx_ && posx_ < that->posx_ + that->width_
        && posy_ > that->posy_ - that->height_ && posy_ - height_ < that->posy_);
}
