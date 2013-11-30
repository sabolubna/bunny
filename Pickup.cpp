#include "Pickup.h"

Pickup::Pickup(int x, int y, int type, int price, ALLEGRO_BITMAP* pickups, ALLEGRO_BITMAP* numbers)
{
    posx_ = x;
    posy_ = y;
    posz_ = 20;
    type_ = type;
    price_ = price;
    width_ = 35;
    height_ = 15;
    pic_height_ = 35;
    pic_width_ = 35;
    picture_ = al_create_sub_bitmap(pickups, type_ * width_, 0, pic_width_, pic_height_);
    numbers_ = numbers;
}

Pickup::~Pickup()
{
    //dtor
}

void Pickup::draw()
{
    Element::draw();
    if (price_>0)
    {
        al_convert_mask_to_alpha(numbers_, al_map_rgb(0, 0, 0));
        al_draw_bitmap_region(numbers_, price_*25, 0, 25, 35, posx_+17, posy_+10, 0);
        al_draw_bitmap_region(numbers_, 250, 0, 25, 35, posx_-8, posy_+10, 0);
    }
}
