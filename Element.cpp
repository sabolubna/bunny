#include "Element.h"

Element::Element()
{
    posz_ = 0;
    step_ = 0;
    speedx_ = 0;
    speedy_ = 0;
    width_ = 80;
    height_ = 80;
}

Element::~Element()
{
    //dtor
}

void Element::dispatchEvent(ALLEGRO_EVENT* event)
{
    if (event->type == ALLEGRO_EVENT_TIMER)
    {
        move();
    }
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

void Element::setPos(int x, int y, int z)
{
    posx_ = x;
    posy_ = y;
    posz_ = z;
}

int* Element::getSize()
{
    int* size = new int[2];
    size[0] = width_;
    size[1] = height_;
    return size;
}

double* Element::getPos()
{
    double* pos = new double[2];
    pos[0] = posx_;
    pos[1] = posy_;
    return pos;
}

void Element::move()
{
    if (posz_ > 0) posz_ -= 1;
    if (speedx_ == 0 && speedy_ == 0) return;
    double sq = sqrt(speedx_*speedx_ + speedy_*speedy_);
    posx_ += 1.0 * speedx_ * step_ / sq;
    posy_ += 1.0 * speedy_ * step_ / sq;
}

void Element::draw()
{
    al_draw_filled_ellipse(posx_+width_/2, posy_- height_/2+5, width_/2, height_/2, al_map_rgba(0,0,0,50));
    al_draw_bitmap(picture_, posx_, posy_ - pic_height_ - posz_, 0);
}

bool Element::collidesWith(Element* that)
{
    return (posx_ + width_ > that->posx_ && posx_ < that->posx_ + that->width_
        && posy_ > that->posy_ - that->height_ && posy_ - height_ < that->posy_);
}
