#include "Bomb.h"

Bomb::Bomb(double* bunnyPos)
{
    picture_ = al_load_bitmap("pics/pickups.png");
    al_convert_mask_to_alpha(picture_, al_map_rgb(255,255,255));
    posx_ = bunnyPos[0] + 7;
    posy_ = bunnyPos[1] + 1;
    posz_ = 0;
    width_ = 35;
    height_ = 15;
    pic_height_ = 35;
    pic_width_ = 35;
    explosionTime_ = al_get_time() + 3;
    state_ = 0;
    color_ = 0;
    exploded_ = false;
    damage_ = 70;
}

Bomb::~Bomb()
{
    //dtor
}

void Bomb::draw()
{
    if (exploded_)
    {
        double timeLeft = explosionTime_ - al_get_time();
        if (timeLeft > -0.1)
                al_draw_tinted_bitmap_region(picture_, al_map_rgba(0,0,0,100), 0, 35, 173, 156, posx_-69, posy_-95, 0);
            else if (timeLeft > -0.2)
                al_draw_tinted_bitmap_region(picture_, al_map_rgba(0,0,0,50), 0, 35, 173, 156, posx_-69, posy_-95, 1);
            else
                al_draw_tinted_bitmap_region(picture_, al_map_rgba(0,0,0,20), 0, 35, 173, 156, posx_-69, posy_-95, 2);
        return;
    }

    al_draw_filled_ellipse(posx_+width_/2, posy_- height_/2+5, width_/2, height_/2, al_map_rgba(0,0,0,50));
    if (color_ == 0)
        al_draw_bitmap_region(picture_, pic_width_, 0, pic_width_, pic_height_, posx_, posy_ - pic_height_, 0);
    else
        al_draw_tinted_bitmap_region(picture_, al_map_rgb(255, 0, 0), pic_width_, 0, pic_width_, pic_height_, posx_, posy_ - pic_height_, 0);
}

void Bomb::dispatchEvent(ALLEGRO_EVENT* event)
{
    if (event->type == ALLEGRO_EVENT_TIMER)
    {
        state_++;
        double timeLeft = explosionTime_ - al_get_time();
        if ((timeLeft < 3 && state_%32 == 0) || (timeLeft < 2 && state_%16 == 0)
            || (timeLeft < 1 && state_%4 == 0))
            color_ = 1 - color_;
    }
}

bool Bomb::inRange(Element* element)
{
    int range = 85;
    double* elementPos = element->getPos();
    int* elementSize = element->getSize();
    double xdistance = posx_ + width_/2 - elementPos[0] - elementSize[0]/2;
    double ydistance = posy_ - height_/2 - elementPos[1] + elementSize[1]/2;
    return range*range > xdistance*xdistance + ydistance*ydistance;
}

bool Bomb::smoke()
{
    return explosionTime_ < al_get_time() && explosionTime_ + 0.3 > al_get_time();
}
