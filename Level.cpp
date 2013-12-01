#include "Level.h"


Level::Level(int levelnum)
{
    srand(time(NULL));
    items_ = al_load_bitmap("pics/items.png");
    al_convert_mask_to_alpha(items_, al_map_rgb(255, 255, 255));

    pickups_ = al_load_bitmap("pics/pickups.png");
    al_convert_mask_to_alpha(pickups_, al_map_rgb(255, 255, 255));

    numbers_ = al_load_bitmap("pics/numbers.bmp");
    al_convert_mask_to_alpha(numbers_, al_map_rgb(0, 0, 0));

    shots_ = al_load_bitmap("pics/shots.png");
    al_convert_mask_to_alpha(shots_, al_map_rgb(255, 255, 255));

    enemies_ = al_load_bitmap("pics/enemies.png");
    al_convert_mask_to_alpha(enemies_, al_map_rgb(255, 255, 255));

    background_ = al_load_bitmap("pics/level01.bmp");
    hearts_ = al_load_bitmap("pics/hearts.bmp");
    bunny_ = new Bunny(shots_);
    firstRoom_ = new Room(bunny_, NORMAL);
    currentRoom_ = firstRoom_;
    Room* nextRoom;
    /*
    EnemyFactory* efactory = new EnemyFactory(firstnum, lastnum, enemies_, shots_, bunny_);
    */
    for (int i = 0; i < 5; i++)
    {
        nextRoom = new Room(bunny_, NORMAL);
        for (int i = 0; i < 3; i++)
            // nextRoom->insert(efactory->create();
            nextRoom->insert(new Enemy(rand()%650+50, rand()%350+150, rand()%2, enemies_, shots_, bunny_));
        nextRoom->insert(new Item(300, 400, rand()%10, 2, items_, numbers_));
        nextRoom->insert(new Pickup(650, 200, rand()%4, 0, pickups_, numbers_));
        currentRoom_->createDoor(nextRoom, DOWN);
        currentRoom_ = nextRoom;
    }
    currentRoom_ = firstRoom_;
    /*
    fscanf(fp,"%s", &bitmapname);
        fscanf(fp, "%d %d %d %d %d %d", &level.bossfirst, &level.bosslast, &level.enemyfirst, &level.enemylast,
            &level.itemfirst, &level.itemlast);
            */
}

Level::~Level()
{
    //dtor
}

void Level::dispatchEvent(ALLEGRO_EVENT* event)
{
    if (event->type == ALLEGRO_EVENT_TIMER)
    {
        if (bunny_->atDoor_ >= 0)
        {
            enter(currentRoom_->rooms_.at(bunny_->atDoor_));
        }
    }
    else if (event->type == ALLEGRO_EVENT_KEY_DOWN
        || event->type == ALLEGRO_EVENT_KEY_UP)
    {
        bunny_->dispatchEvent(event);
    }
    currentRoom_->dispatchEvent(event);
}

void Level::enter(Room* room)
{
    currentRoom_->leave();
    currentRoom_ = room;
    room->enter();
    switch (bunny_->atDoor_)
    {
        case 0: bunny_->setPos(700, 345, 0); break;
        case 1: bunny_->setPos(375, 550, 0); break;
        case 2: bunny_->setPos(50, 345, 0); break;
        case 3: bunny_->setPos(375, 140, 0); break;
    }
    bunny_->atDoor_ = -1;
}

void Level::draw()
{
    al_draw_bitmap(background_, 0, 0, 0);
    //drawing hearts
    int i = 0;
    while(i < 2 * bunny_->hearts_)
    {
        if (bunny_->hp_-i >= 2)
        {
            al_draw_bitmap_region(hearts_,39,0,39,35,525+i*45/2,8,0);
        }
        else if (bunny_->hp_-i == 1)
        {
            al_draw_bitmap_region(hearts_,0,0,39,35,525+i*45/2,8,0);
        }
        else
        {
            al_draw_bitmap_region(hearts_,78,0,39,35,525+i*45/2,8,0);
        }
        i+=2;
    }
    // drawing numbers
    if (bunny_->coins_>=10)
    {
        al_draw_bitmap_region(numbers_,(bunny_->coins_/10)*25,0,25,35,160,10,0);
        al_draw_bitmap_region(numbers_,(bunny_->coins_ % 10)*25,0,25,35,185,10,0);
    }
    else al_draw_bitmap_region(numbers_,(bunny_->coins_ % 10)*25,0,25,35,160,10,0);
    if (bunny_->bombs_>=10)
    {
        al_draw_bitmap_region(numbers_,(bunny_->bombs_/10)*25,0,25,35,260,10,0);
        al_draw_bitmap_region(numbers_,(bunny_->bombs_ % 10)*25,0,25,35,285,10,0);
    }
    else al_draw_bitmap_region(numbers_,(bunny_->bombs_ % 10)*25,0,25,35,260,10,0);
    if (bunny_->keys_>=10)
    {
        al_draw_bitmap_region(numbers_,(bunny_->keys_/10)*25,0,25,35,360,10,0);
        al_draw_bitmap_region(numbers_,(bunny_->keys_ % 10)*25,0,25,35,385,10,0);
    }
    else al_draw_bitmap_region(numbers_,(bunny_->keys_ % 10)*25,0,25,35,360,10,0);
    currentRoom_->draw();
}
