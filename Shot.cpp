#include "Shot.h"

Shot::Shot(ALLEGRO_BITMAP *pic, int posx, int posy, int posz, double speedx, double speedy,
             double range, bool hurtsBunny, int dmg)
{
    picture_ = pic;
    posx_ = posx;
    posy_ = posy;
    posz_ = posz;
    speedx_ = speedx;
    speedy_ = speedy;
    range_ = range;
    hurtsBunny_ = hurtsBunny;
    damage_ = dmg;
    step_ = 5;
    width_ = 20;
    height_ = 20;
    pic_width_ = 20;
    pic_height_ = 20;
}

Shot::~Shot()
{
    //dtor
}

void Shot::move()
{
    double stepx, stepy;
    double sq = speedx_*speedx_ + speedy_*speedy_;
    stepx = speedx_ * step_ / sqrt(sq);
    stepy = speedy_ * step_ / sqrt(sq);
    posx_ += stepx;
    posy_ += stepy;
    posz_ -= posz_ / range_;
    range_ -= step_;
}

void Shot::bounceFromWall(int borders[4])
{
    if (posx_ < borders[LEFT] || posx_ + width_ > borders[RIGHT]
        || posy_ > borders[DOWN] || posy_ - height_ < borders[UP])
        range_ = 0;
}
