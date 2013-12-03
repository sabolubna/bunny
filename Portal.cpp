#include "Portal.h"

Portal::Portal()
{
    animationState_ = 0;
    animationTime_ = 0.1;
    lastAnimation_ = al_get_time();
    picture_ = al_load_bitmap("pics/portal.png");
    al_convert_mask_to_alpha(picture_, al_map_rgb(0, 0, 0));
    width_ = 242/4;
    height_ = 95/4;
    posx_ = 370;
    posy_ = 230;
    posz_ = 0;
    pic_height_ = height_;
    pic_width_ = width_;
    locked_ = true;
}

Portal::~Portal()
{
    //dtor
}

void Portal::dispatchEvent(ALLEGRO_EVENT* event)
{
    if (event->type == ALLEGRO_EVENT_TIMER)
    {
        if (animationTime_ < al_get_time() - lastAnimation_)
        {
            animationState_++;
            lastAnimation_ = al_get_time();
            if (animationState_ > 5)
                animationState_ = 0;
        }
    }
}

void Portal::draw()
{
    al_draw_scaled_bitmap(picture_, animationState_ * 242, 0, 242, 95, posx_, posy_ - pic_height_,
                          pic_width_,pic_height_,0);
}
