#include "SpaceItem.h"

SpaceItem::SpaceItem(ALLEGRO_BITMAP* picture, int num)
{
    picture_ = picture;
    number_ = num;
    roomsLeft_ = 0;
    numbers_ = al_load_bitmap("pics/numbers.bmp");
}

SpaceItem::~SpaceItem()
{
    //dtor
}

void SpaceItem::draw()
{
    if (roomsLeft_ <= 0)
        al_draw_bitmap(picture_, 5, 5, 0);
    else
    {
        al_draw_bitmap_region(numbers_, roomsLeft_*25,0,25,35,60,10,0);
        al_draw_tinted_bitmap(picture_, al_map_rgba(255,255,255,100), 5, 5, 0);
    }
}

void SpaceItem::onSpace(RoomEffect* room, Bunny* bunny)
{
    if (roomsLeft_ > 0) return;
    switch(number_)
    {
        case 3: // carrot bag
        {
            if (bunny->hp_ < bunny->hearts_*2)
            {
                bunny->hp_ += 2;
                if (bunny->hp_ > bunny->hearts_*2)
                    bunny->hp_ = bunny->hearts_*2;
                roomsLeft_ = 4;
            }
            break;
        }
        case 4: //random pickup
        {
            int random;
            random = rand()%3;
            room->newPickup();
            roomsLeft_ = 3;
            break;
        }
        case 13: // squirtle's glasses DEAL WITH IT
        {
            room->oneRoomEffect(SHOTTIME, 0.1 - bunny->shotTime_);
            bunny->shotTime_ = 0.1;
            roomsLeft_ = 5;
            break;
        }
    }
    if (bunny->battery_ > 0)
    {
        roomsLeft_ -= bunny->battery_;
        if (roomsLeft_ < 1) roomsLeft_ = 1;
    }
    return;
}
