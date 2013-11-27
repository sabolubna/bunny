#include "Bunny.h"

using namespace std;

Bunny::Bunny()
{
    picture_ = al_load_bitmap("pics/bunny.png");
    al_convert_mask_to_alpha(picture_, al_map_rgb(255,0,0));
    width_ = 50;
    pic_width_ = 50;
    height_ = 30;
    pic_height_ = 98;
    posx_ = 50;
    posy_ = 300;
    posz_ = 0;
    step_ = 3;
    speedx_ = 0;
    speedy_ = 0;
    animationTime_ = 0.09;
    lastAnimation_ = al_get_time() - animationTime_;
    jumpState_ = 0;
    atDoor_ = -1;
    keys_ = 1;
    bombs_ = 1;
    coins_ = 3;
    hearts_ = 3;
    hp_ = 6;
    for (int i = 0; i < ITEM_CNT; i++)
    {
        itemsCollected[i] = false;
    }
}

Bunny::~Bunny()
{
    //dtor
}

void Bunny::draw()
{
    int dir = 0;
    if (speedx_ != 0)
    {
        dir = -speedx_+2;
    }
    else if (speedy_ < 0)
    {
        dir = 2;
    }
    int a;
    switch (jumpState_)
    {
        case 0: a = 0; break;
        case 1: a = 1; break;
        case 2: a = 2; break;
        case 3: a = 2; break;
        case 4: a = 1; break;
        case 5: a = 0; break;
    }
    if (jumpState_ >= 5)
        jumpState_ = 0;
    al_draw_filled_ellipse(posx_+width_/2, posy_- height_/2+5, width_/2, height_/2, al_map_rgba(0,0,0,50));
   // if (game->bunny.immortal < al_get_time())
        al_draw_scaled_bitmap(picture_,0+a*200,0+dir*392,200,392,posx_,posy_-90,50,98,0);
    //else
        //al_draw_tinted_scaled_bitmap(game->bunny.picture,al_map_rgba(200,100,100,100),0+a*200,
                        //0+game->bunny.statey*392,200,392,game->bunny.posx,game->bunny.posy-90,50,98,0);
}

void Bunny::dispatchEvent(ALLEGRO_EVENT* event)
{
    if (event->type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if (event->keyboard.keycode == ALLEGRO_KEY_W)
        {
            changeSpeedBy(0, -1);
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_D)
        {
            changeSpeedBy(1, 0);
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_S)
        {
            changeSpeedBy(0, 1);
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_A)
        {
            changeSpeedBy(-1, 0);
        }
    }
    if (event->type == ALLEGRO_EVENT_KEY_UP)
    {
        if (event->keyboard.keycode == ALLEGRO_KEY_W)
        {
            changeSpeedBy(0, 1);
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_D)
        {
            changeSpeedBy(-1, 0);
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_S)
        {
            changeSpeedBy(0, -1);
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_A)
        {
            changeSpeedBy(1, 0);
        }
    }
    if (event->type == ALLEGRO_EVENT_TIMER)
    {
        if (animationTime_ < al_get_time() - lastAnimation_ && ((speedx_ != 0 || speedy_ != 0) || jumpState_ != 0))
        {
            jumpState_++;
            lastAnimation_ = al_get_time();
        }
        move();
    }
}

void Bunny::setPos(int x, int y, int z)
{
    posx_ = x;
    posy_ = y;
    posz_ = z;
}

void Bunny::handleCollision(Door* door)
{
    if (door->fits(posx_, posy_, width_, height_) && !door->locked_ && (!door->keyNeeded_ || keys_ > 0))
    {
        atDoor_ = door->side_;
    }
}

int Bunny::handleCollision(Item* item)
{
    if (coins_ >= item->price_)
    {
        itemsCollected[item->number_] = true;
        coins_ -= item->price_;
        return 1;
    }
}
