#include "Element.h"

Element::Element()
{
    //ctor
}

Element::~Element()
{
    //dtor
}

int Element::compareTo(Element that)
{
    if (this->posy > that.posy) return 1;
    if (this->posy < that.posy) return -1;
    if (this->posy < that.posy) return -1;
    if (this->posy > that.posy) return 1;
    return 0;
}

bool Element::collides(Element that)
{
    return (this->posx + this->length > that.posx
        && this->posx < that.posx + that.length
        && this->posy > that.posy - that.width
        && this->posy - this->width < that.posy);
}

void Element::wall(Room* room)
{
    if (posx < room->leftborder) posx = room->leftborder+1;
    if (posx + length > room->rightborder) posx = room->rightborder-1-length;
    if (posy > room->downborder) posy = room->downborder - 1;
    if (posy - width < room->upborder) posy = room->upborder+1+width;
}

void Element::changeSpeed(int x, int y)
{
    speedx += x;
    speedy += y;
}

void Element::setSpeed(int x, int y)
{
    speedx = x;
    speedy = y;
}

void Element::move()
{
    if (speedx == 0 && speedy == 0) return;
    double sq = sqrt(pow(speedx,2)+pow(speedy,2));
    posx += 1.0 * speedx * step / sq;
    posy += 1.0 * speedy * step / sq;
}

void Element::draw()
{
    al_draw_bitmap(picture, posx, posy - height - posz, 0);
}


