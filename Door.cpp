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
    if (type == SHOP || type == TREASURE)
        keyNeeded_ = true;
    else
        keyNeeded_ = false;
    locked_ = false;
    doorspic_ = al_load_bitmap("pics/doors.png");
    al_convert_mask_to_alpha(doorspic_, al_map_rgb(255,255,255));
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
        picture_ = al_create_sub_bitmap(doorspic_, 0, 0, width_, height_*7+11);
    else
        picture_ = al_create_sub_bitmap(doorspic_, 45, 0, width_+4, width_*7+11);
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

void Door::open()
{
    if (type_ == TREASURE)
        type_ = TREASUREOPEN;
    if (type_ == SHOP)
        type_ = NORMAL;
    keyNeeded_ = false;
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
    al_draw_bitmap_region(picture_, 0, 80*type_, width_, height_, posx_, posy_ - height_, flag);
    if (locked_)
        switch(side_)
        {
            case LEFT: al_draw_bitmap_region(picture_, 0, 560, width_+4, height_+11, posx_ - 5, posy_ - height_ - 5, flag); break;
            case UP: al_draw_bitmap_region(picture_, 5, 560, width_+11, height_+4, posx_ - 5, posy_ - height_ - 5, flag); break;
            case RIGHT: al_draw_bitmap_region(picture_, 0, 560, width_+4, height_+11, posx_, posy_ - height_ - 5, flag); break;
            case DOWN: al_draw_bitmap_region(picture_, 5, 560, width_+11, height_+4, posx_ - 5, posy_ - height_, flag); break;
        }
}
