#include "Item.h"

Item::Item(int x, int y, int num, int price, ALLEGRO_BITMAP* items, ALLEGRO_BITMAP* numbers)
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
    picture_ = al_create_sub_bitmap(items, number_%10*45, number_/10*45, 45, 45);
    numbers_ = numbers;
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

/*void activate()
{
    double tmp;
    switch (num)
    {
        case 0: //rabbits heart
        {
            game->bunny.hearts++;
            game->bunny.hp+=2;
            break;
        }
        case 1: // coin bag
        {
            game->coins+=10;
            if (game->coins > 99)
                game->coins = 99;
            break;
        }
        case 2: // plonaca kapucha
        {
            game->bunny.shotpic = al_create_sub_bitmap(game->shotpics,60,0,20,20);
            game->bunny.range += 200;
            break;
        }
        case 3: // worek marchewek
        {
            if (game->spaceitem >= 0)
            {
                game->room->items[i].number = game->spaceitem;
                game->room->items[i].taken = 0;
                tmp = game->spaceleft;
                game->spaceleft = game->room->items[i].spaceleft;
                game->room->items[i].spaceleft = tmp;
            }
            game->spaceitem = 3;
            break;
        }
        case 4: // mystery worek
        {
            if (game->spaceitem >= 0)
            {
                game->room->items[i].number = game->spaceitem;
                game->room->items[i].taken = 0;
                tmp = game->spaceleft;
                game->spaceleft = game->room->items[i].spaceleft;
                game->room->items[i].spaceleft = tmp;
            }
            game->spaceitem = 4;
            break;
        }
        case 5: // candy rush
        {
            game->bunny.speed -= 0.001;
            game->bunny.kicspeed -= 0.02;
            break;
        }
        case 6: // bomb bag
        {
            game->bombs += 10;
            if (game->bombs > 99)
                game->bombs = 99;
            break;
        }
        case 7: // key bag
        {
            game->keys += 10;
            if (game->keys > 99)
                game->keys = 99;
            break;
        }
        case 8: //lasergun
        {
            game->bunny.shottype = 1;
            game->bunny.shotfreq = 0.6;
            game->bunny.range = 700;
            break;
        }
        case 9: //duracell
        {
            game->bunny.battery += 2;
            break;
        }
        case 10: // buciki
        {
            game->bunny.boots += 1;
            break;
        }
        //bonus items
        //pokemon level
        case 15: //lvlup candy
        {
            game->bunny.dmg += 10;
            if (game->bunny.dmg > 60)
                game->bunny.dmg = 60;
            game->bunny.shotfreq -= 0.1;
            if (game->bunny.shotfreq < 0.1)
                game->bunny.shotfreq = 0.1;
            game->bunny.range += 80;
            if (game->bunny.range > 700)
                game->bunny.range = 700;
            game->bunny.speed -= 0.001;
            if (game->bunny.speed < 0.004)
                game->bunny.speed = 0.004;
            game->bunny.hearts++;
            if (game->bunny.hearts > 6)
            {
                game->bunny.hearts = 6;
                game->bunny.hp = game->bunny.hearts*2;
            }
            break;
        }
        case 16: // pokeball
        {
            game->bunny.shotpic = al_create_sub_bitmap(game->shotpics,41,0,20,20);
            break;
        }
        case 17: // squirtle's glasses
        {
            if (game->spaceitem >= 0)
            {
                game->room->items[i].number = game->spaceitem;
                game->room->items[i].taken = 0;
                tmp = game->spaceleft;
                game->spaceleft = game->room->items[i].spaceleft;
                game->room->items[i].spaceleft = tmp;
            }
            game->spaceitem = 17;
            break;
        }
        case 18: // ash cap GOTTA CATCH EM ALL
        {
            newpickup(game, game->room, 0, rand()%665+50, rand()%415+100,0);
            newpickup(game, game->room, 1, rand()%665+50, rand()%415+100,0);
            newpickup(game, game->room, 2, rand()%665+50, rand()%415+100,0);
            newpickup(game, game->room, 3, rand()%665+50, rand()%415+100,0);
            break;
        }
        case 51: // niebieski portalgun
        {
            if (game->spaceitem >= 0)
            {
                game->room->items[i].number = game->spaceitem;
                game->room->items[i].taken = 0;
                tmp = game->spaceleft;
                game->spaceleft = game->room->items[i].spaceleft;
                game->room->items[i].spaceleft = tmp;
            }
            game->spaceitem = 3;
            break;
        }
        case 52: //pomaranczowy portal gun
        {
            if (game->spaceitem >= 0)
            {
                game->room->items[i].number = game->spaceitem;
                game->room->items[i].taken = 0;
                tmp = game->spaceleft;
                game->spaceleft = game->room->items[i].spaceleft;
                game->room->items[i].spaceleft = tmp;
            }
            game->spaceitem = 4;
            break;
        }
    }
}*/

