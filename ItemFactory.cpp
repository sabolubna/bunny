#include "ItemFactory.h"

ItemFactory::ItemFactory(Bunny* bunny)
{
    items_ = al_load_bitmap("pics/items.png");
    al_convert_mask_to_alpha(items_, al_map_rgb(255, 255, 255));

    numbers_ = al_load_bitmap("pics/numbers.bmp");
    al_convert_mask_to_alpha(numbers_, al_map_rgb(0, 0, 0));

    bunny_ = bunny;
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
    if (type == BOSS)
    {
        int r = rand()%(lastItem_ - firstItem_ + 1) + firstItem_;
        while (bunny_->itemsCollected[r])
        {
            r = rand()%(lastItem_ - firstItem_ + 1) + firstItem_;
        }
        bunny_->itemsCollected[r] = true;
        ALLEGRO_BITMAP* picture = al_create_sub_bitmap(items_, r%10*45, r/10*45, 45, 45);
        Item* item = new Item(378, 450, r, 0, picture, numbers_);
        return item;
    }
    else
    {
        int r = rand()%(lastItem_ - firstItem_ + 1) + firstItem_;
        while (bunny_->itemsCollected[r])
        {
            r = rand()%(lastItem_ - firstItem_ + 1) + firstItem_;
        }
        ALLEGRO_BITMAP* picture = al_create_sub_bitmap(items_, r%10*45, r/10*45, 45, 45);
        Item* item = new Item(378, 308, r, 0, picture, numbers_);
        return item;
    }
}
