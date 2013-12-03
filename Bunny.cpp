#include "Bunny.h"


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
    atPortal_ = false;
    keys_ = 1;
    bombs_ = 1;
    coins_ = 3;
    hearts_ = 3;
    hp_ = 6;
    for (int i = 0; i < ITEM_CNT; i++)
    {
        itemsCollected[i] = false;
    }
    shotTime_ = 0.6;
    lastShot_ = al_get_time() - shotTime_;
    shots_ = al_load_bitmap("pics/shots.png");
    al_convert_mask_to_alpha(shots_, al_map_rgb(255, 255, 255));
    shotPicture_ = al_create_sub_bitmap(shots_, 0, 0, 20, 20);
    range_ = 300;
    damage_ = 10;
    shooting_ = false;
    immunityTime_ = al_get_time();
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
    if (immunityTime_ < al_get_time())
        al_draw_scaled_bitmap(picture_,0+a*200,0+dir*392,pic_width_*4,pic_height_*4,posx_,posy_-90,pic_width_,pic_height_,0);
    else
        al_draw_tinted_scaled_bitmap(picture_,al_map_rgba(200,100,100,100),0+a*200,0+dir*392,pic_width_*4,pic_height_*4,posx_,
                                     posy_-90,pic_width_,pic_height_,0);
}

void Bunny::dispatchEvent(ALLEGRO_EVENT* event)
{
    if (event->type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if (event->keyboard.keycode == ALLEGRO_KEY_W)
        {
            changeSpeedBy(0, -1);
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_D)
        {
            changeSpeedBy(1, 0);
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_S)
        {
            changeSpeedBy(0, 1);
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_A)
        {
            changeSpeedBy(-1, 0);
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_LEFT)
        {
            shotDirection_ = LEFT;
            shooting_ = true;
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_UP)
        {
            shotDirection_ = UP;
            shooting_ = true;
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_RIGHT)
        {
            shotDirection_ = RIGHT;
            shooting_ = true;
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            shotDirection_ = DOWN;
            shooting_ = true;
            return;
        }
    }
    if (event->type == ALLEGRO_EVENT_KEY_UP)
    {
        if (event->keyboard.keycode == ALLEGRO_KEY_W)
        {
            changeSpeedBy(0, 1);
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_D)
        {
            changeSpeedBy(-1, 0);
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_S)
        {
            changeSpeedBy(0, -1);
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_A)
        {
            changeSpeedBy(1, 0);
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_LEFT && shotDirection_ == LEFT)
        {
            shooting_ = false;
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_UP && shotDirection_ == UP)
        {
            shooting_ = false;
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_RIGHT && shotDirection_ == RIGHT)
        {
            shooting_ = false;
            return;
        }
        if (event->keyboard.keycode == ALLEGRO_KEY_DOWN && shotDirection_ == DOWN)
        {
            shooting_ = false;
            return;
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

int Bunny::handleCollision(Pickup* pickup)
{
    if (coins_ < pickup->price_ || (hp_ == 2*hearts_ && pickup->type_ == 3))
        return 0;
    coins_ -= pickup->price_;
    switch (pickup->type_)
    {
        case 0: if (coins_ < 99) coins_++; break;
        case 1: if (bombs_ < 99) bombs_++; break;
        case 2: if (keys_<99) keys_++; break;
        case 3: hp_++; break;
    }
    return 1;
}

Shot* Bunny::shoot()
{
    if (al_get_time() > lastShot_ + shotTime_ && shooting_)
    {
        lastShot_ = al_get_time();
        int shotSpeedx, shotSpeedy;
        if (shotDirection_ == LEFT || shotDirection_ == RIGHT)
        {
            shotSpeedy = 0;
            if (shotDirection_ == LEFT)
                shotSpeedx = -1;
            else
                shotSpeedx = 1;
        }
        if (shotDirection_ == UP || shotDirection_ == DOWN)
        {
            shotSpeedx = 0;
            if (shotDirection_ == UP)
                shotSpeedy = -1;
            else
                shotSpeedy = 1;
        }
        return new Shot(shotPicture_, posx_ + width_/2 - 10, posy_+1, 30, shotSpeedx, shotSpeedy,
             range_, false, damage_);
    }
    return NULL;
}

void Bunny::hurt(int damage)
{
    if (immunityTime_ < al_get_time())
    {
        hp_ -= damage;
        immunityTime_ = al_get_time() + 1;
    }
}

bool Bunny::alive()
{
    return hp_ > 0;
}
