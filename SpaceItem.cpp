#include "SpaceItem.h"

SpaceItem::SpaceItem(ALLEGRO_BITMAP* picture, int num)
{
    picture_ = picture;
    number_ = num;
    roomsLeft_ = 0;
}

SpaceItem::~SpaceItem()
{
    //dtor
}

void SpaceItem::draw()
{
    al_draw_bitmap(picture_, 5, 5, 0);
}

void SpaceItem::onSpace(Bunny* bunny)
{
    if (roomsLeft_ > 0) return;
    /*switch(number_)
    {
        case 3: // worek marchewek
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
    }/*
        case 4: //mystery worek
        {
            int random;
            random = rand()%3+1;
            if (random == 1) random = 0;
            newpickup(game, game->room, random, rand()%665+50, rand()%415+100,0);
            roomsLeft_ = 2;
            break;
        }
        case 17: // squirtle's glasses DEAL WITH IT
        {
            //al_draw_bitmap_region(game->pickups,);
            game->roomeffect[0] = 0.1 - game->bunny.shotfreq;
            game->bunny.shotfreq = 0.1;
            roomsLeft_ = 3;
            break;
        }
    }
    if (game->bunny.battery > 0)
    {
        roomsLeft_ -= game->bunny.battery;
        if (roomsLeft_ < 1) roomsLeft_ = 1;
    }*/
    return;
}
