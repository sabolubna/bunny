#include "Item.h"

Item::Item(int x, int y, int num, int price, ALLEGRO_BITMAP* picture, ALLEGRO_BITMAP* numbers, ALLEGRO_BITMAP* shots)
{
    posx_ = x;
    posy_ = y;
    posz_ = 20;
    width_ = 45;
    height_ = 20;
    pic_width_ = 45;
    pic_height_ = 45;
    number_ = num;
    price_ = price;
    picture_ = picture;
    numbers_ = numbers;
    shots_ = shots;
    roomsLeft_ = 0;
}

Item::~Item()
{
    //dtor
}

void Item::draw()
{
    Element::draw();
    if (price_ > 0)
    {
        if (price_ >= 10)
        {
            al_draw_bitmap_region(numbers_,(price_/10)*25,0,25,35,posx_+12,posy_+10,0);
            al_draw_bitmap_region(numbers_,(price_ % 10)*25,0,25,35,posx_+37,posy_+10,0);
            al_draw_bitmap_region(numbers_,250,0,25,35,posx_-13,posy_+10,0);
        }
        else
        {
            al_draw_bitmap_region(numbers_,(price_ % 10)*25,0,25,35,posx_+22,posy_+10,0);
            al_draw_bitmap_region(numbers_,250,0,25,35,posx_-3,posy_+10,0);
        }
    }
}

bool Item::handleCollision(Bunny* bunny, RoomEffect* room, SpaceItem* spaceItem)
{
    if (bunny->coins_ >= price_)
    {
        bunny->itemsCollected[number_] = true;
        bunny->coins_ -= price_;
        return activate(bunny, room, spaceItem);
    }
    return false;
}

bool Item::lying()
{
    return posz_ == 0;
}

bool Item::pickUpSpaceItem(SpaceItem* spaceItem)
{
    if (spaceItem->number_ > 0)
    {
        ALLEGRO_BITMAP* pic;
        pic = picture_;
        picture_ = spaceItem->picture_;
        spaceItem->picture_ = pic;
        int num = number_;
        number_ = spaceItem->number_;
        spaceItem->number_ = num;
        int left = roomsLeft_;
        roomsLeft_ = spaceItem->roomsLeft_;
        spaceItem->roomsLeft_ = left;
        posz_ = 20;
        return false;
    }
    spaceItem->picture_ = picture_;
    spaceItem->number_ = number_;
    return true;
}

bool Item::activate(Bunny* bunny, RoomEffect* room, SpaceItem* spaceItem)
{
    switch (number_)
    {
        case 0: //rabbits heart
        {
            bunny->hearts_++;
            bunny->hp_ += 2;
            break;
        }
        case 1: // coin bag
        {
            bunny->coins_ += 10;
            if (bunny->coins_ > 99)
                bunny->coins_ = 99;
            break;
        }
        case 2: // plonaca kapucha
        {
            bunny->shotPicture_ = al_create_sub_bitmap(shots_,80,0,20,20);
            bunny->range_ += 200;
            break;
        }
        case 3: // worek marchewek
        {
            return pickUpSpaceItem(spaceItem);
        }
        case 4: // mystery worek
        {
            return pickUpSpaceItem(spaceItem);
        }
        case 5: // candy rush
        {
            bunny->step_ += 0.5;
            if (bunny->step_ > 6)
                bunny->step_ = 6;
            bunny->animationTime_ -= 0.02;
            if (bunny->animationTime_ < 0.03)
                bunny->animationTime_ = 0.03;
            break;
        }
        case 6: // bomb bag
        {
            bunny->bombs_ += 10;
            if (bunny->bombs_ > 99)
                bunny->bombs_ = 99;
            break;
        }
        case 7: // key bag
        {
            bunny->keys_ += 10;
            if (bunny->keys_ > 99)
                bunny->keys_ = 99;
            break;
        }
        case 8: //lasergun
        {
            bunny->damage_ += 10;
            if (bunny->damage_ > 60)
                bunny->damage_ = 60;
            break;
        }
        case 9: //duracell
        {
            bunny->battery_ += 2;
            break;
        }
        case 10: // boots
        {
            bunny->boots_ = true;
            break;
        }
        //pokemon level
        case 11: //lvlup candy
        {
            bunny->damage_ += 10;
            if (bunny->damage_ > 60)
                bunny->damage_ = 60;
            bunny->shotTime_ -= 0.1;
            if (bunny->shotTime_ < 0.1)
                bunny->shotTime_ = 0.1;
            bunny->range_ += 80;
            if (bunny->range_ > 700)
                bunny->range_ = 700;
            bunny->step_ += 0.5;
            if (bunny->step_ > 6)
                bunny->step_ = 6;
            bunny->hearts_++;
            if (bunny->hearts_ > 6)
            {
                bunny->hearts_ = 6;
                bunny->hp_ = bunny->hearts_*2;
            }
            break;
        }
        case 12: // pokeball
        {
            bunny->shotPicture_ = al_create_sub_bitmap(shots_,60,0,20,20);
            break;
        }
        case 13: // squirtle's glasses
        {
            return pickUpSpaceItem(spaceItem);
        }
        case 14: // ash cap GOTTA CATCH EM ALL
        {
            room->newPickup(CARROT);
            room->newPickup(BOMB);
            room->newPickup(KEY);
            room->newPickup(COIN);
            break;
        }
    }
    return true;
}
