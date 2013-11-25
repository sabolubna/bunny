#include "Door.h"

Door::Door(Side side, RoomType type)
{
    init(side, type);
}

Door::Door(int num, RoomType type)
{
    Side side;
    switch (num)
    {
        case 0: side = LEFT; break;
        case 1: side = UP; break;
        case 2: side = RIGHT; break;
        case 3: side = DOWN; break;
    }
    if (num < 4)
        init(side, type);
}

void Door::init(Side side, RoomType type)
{
    type_ = type;
    keyNeeded_ = false;
    locked_ = false;
    ALLEGRO_BITMAP* doors = al_load_bitmap("pics/doors.png");
    al_convert_mask_to_alpha(doors, al_map_rgb(255,255,255));
    side_ = side;
    switch (side)
    {
        case LEFT:
        {
            posx_ = 5;
            posy_ = 365;
            width_ = 45;
            height_ = 80;
            break;
        }
        case UP:
        {
            posx_ = 360;
            posy_ = 100;
            width_ = 80;
            height_ = 45;
            break;
        }
        case RIGHT:
        {
            posx_ = 750;
            posy_ = 365;
            width_ = 45;
            height_ = 80;
            break;
        }
        case DOWN:
        {
            posx_ = 360;
            posy_ = 595;
            width_ = 80;
            height_ = 45;
            break;
        }
    }
    if (side_ == LEFT || side_ == RIGHT)
        picture_ = al_create_sub_bitmap(doors, 0, 0, width_, height_*7);
    else
        picture_ = al_create_sub_bitmap(doors, 45, 0, width_, width_*7);
    pic_width_ = width_;
    pic_height_ = height_;
}

Door::~Door()
{
    //dtor
}

void Door::bounceFromWall(int borders[4])
{
    return;
}

void Door::unlock()
{
    locked_ = false;
}

void Door::lock()
{
    locked_ = true;
}

bool Door::fits(int posx, int posy, int width, int height)
{
    if (side_ == LEFT || side_ == RIGHT)
        return (posy < posy_ && posy - height > posy_ - height_);
    if (side_ == UP || side_ == DOWN)
        return (posx > posx_ && posx + width < posx_ + width_);
}

void Door::draw()
{
    int flag = 0;
    if (side_ == RIGHT) flag = 1;
    else if (side_ == DOWN) flag = 2;
    //al_draw_bitmap(picture_, posx_, posy_ - height_, flag);
    al_draw_bitmap_region(picture_, 0, 80*type_, width_, height_, posx_, posy_ - height_, flag);
}
