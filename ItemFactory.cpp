#include "ItemFactory.h"

ItemFactory::ItemFactory()
{
    items_ = al_load_bitmap("pics/items.png");
    al_convert_mask_to_alpha(items_, al_map_rgb(255, 255, 255));

    shots_ = al_load_bitmap("pics/shots.png");
    al_convert_mask_to_alpha(shots_, al_map_rgb(255, 255, 255));

    numbers_ = al_load_bitmap("pics/numbers.bmp");
    al_convert_mask_to_alpha(numbers_, al_map_rgb(0, 0, 0));

    for (int i = 0; i < ITEM_CNT; i++)
    {
        itemsDropped[i] = false;
    }
}

ItemFactory::~ItemFactory()
{
    //dtor
}

void ItemFactory::setRange(int first, int last)
{
    firstItem_ = first;
    lastItem_ = last;
}

Item* ItemFactory::create(RoomType type)
{
    int r;
    if (type == BOSS)
    {
        do
        {
            if (rand()%2 == 0)
                r = rand()%(LASTUNIVERSALITEM - FIRSTUNIVERSALITEM + 1) + FIRSTUNIVERSALITEM;
            else
                r = rand()%(lastItem_ - firstItem_ + 1) + firstItem_;
        } while (itemsDropped[r]);
        itemsDropped[r] = true;
        ALLEGRO_BITMAP* picture = al_create_sub_bitmap(items_, r%10*45, r/10*45, 45, 45);
        Item* item = new Item(378, 450, r, 0, picture, numbers_, shots_);
        return item;
    }
    if (type == SHOP)
    {
        do
        {
            r = rand()%(LASTSHOPITEM - FIRSTSHOPITEM + 1) + FIRSTSHOPITEM;
        } while (itemsDropped[r]);
        itemsDropped[r] = true;
        ALLEGRO_BITMAP* picture = al_create_sub_bitmap(items_, r%10*45, r/10*45, 45, 45);
        Item* item = new Item(328, 308, r, rand()%3*5+5, picture, numbers_, shots_);
        return item;
    }
    if (type == TREASURE)
    {
        do
        {
            if (rand()%2 == 0)
                r = rand()%(LASTUNIVERSALITEM - FIRSTUNIVERSALITEM + 1) + FIRSTUNIVERSALITEM;
            else
                r = rand()%(lastItem_ - firstItem_ + 1) + firstItem_;
        } while (itemsDropped[r]);
        itemsDropped[r] = true;
        ALLEGRO_BITMAP* picture = al_create_sub_bitmap(items_, r%10*45, r/10*45, 45, 45);
        Item* item = new Item(378, 308, r, 0, picture, numbers_, shots_);
        return item;
    }
    if (type == BONUS)
    {
        itemsDropped[0] = true;
        ALLEGRO_BITMAP* picture = al_create_sub_bitmap(items_, 0%10*45, 0/10*45, 45, 45);
        Item* item = new Item(378, 308, 0, 0, picture, numbers_, shots_);
        return item;
    }
    else
    {
        do
        {
            r = rand()%(lastItem_ - firstItem_ + 1) + firstItem_;
        } while (itemsDropped[r]);
        itemsDropped[r] = true;
        ALLEGRO_BITMAP* picture = al_create_sub_bitmap(items_, r%10*45, r/10*45, 45, 45);
        Item* item = new Item(378, 308, r, 0, picture, numbers_, shots_);
        return item;
    }
}
