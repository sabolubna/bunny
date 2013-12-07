#include "Level.h"

Level::Level()
{
    srand(time(NULL));

    numbers_ = al_load_bitmap("pics/numbers.bmp");
    al_convert_mask_to_alpha(numbers_, al_map_rgb(0, 0, 0));

    background_ = al_load_bitmap("pics/level01.bmp");
    hearts_ = al_load_bitmap("pics/hearts.bmp");
    bunny_ = new Bunny();

    efactory_ = new EnemyFactory(bunny_);
    ifactory_ = new ItemFactory();
    pfactory_ = new PickupFactory();

    for (int i = 0; i < LVL_CNT; i++)
    {
        usedLevels_[i] = false;
    }
    levelsPlayed_ = 0;
    playing_ = true;
    nextLevel();
}

Level::~Level()
{
    //dtor
}

void Level::nextLevel()
{
    printf("nextLevel\n");
    if (levelsPlayed_ == LVL_CNT)
    {
        printf("win\n");
        playing_ = false;
        return;
    }
    bunny_->setPos(375, 400, 30);
    int type = rand()%LVL_CNT;
    while (usedLevels_[type])
    {
        type = rand()%LVL_CNT;
    }
    usedLevels_[type] = true;
    levelsPlayed_++;

    fstream file;
    file.open("files/levels.txt", ios::in);
    for (int i = 0; i < type; i++)
    {
        string s;
        getline(file, s);
    }
    int firstItem, lastItem, firstEnemy, lastEnemy;
    file >> firstItem;
    file >> lastItem;
    file >> firstEnemy;
    file >> lastEnemy;
    ifactory_->setRange(firstItem, lastItem);
    efactory_->setRange(firstEnemy, lastEnemy);
    //creating floor
    firstRoom_ = new Room(bunny_, NORMAL, ifactory_, pfactory_);
    currentRoom_ = firstRoom_;
    Room* nextRoom;
    int roomCount = 4;
    for (int i = 0; i < roomCount; i++)
    {
        nextRoom = new Room(bunny_, NORMAL, ifactory_, pfactory_);
        int eCount = rand()%3+1;
        for (int i = 0; i < eCount; i++)
            nextRoom->insert(efactory_->create());
        currentRoom_->createDoor(nextRoom, RIGHT);
        currentRoom_ = nextRoom;
    }
    nextRoom = new Room(bunny_, BOSS, ifactory_, pfactory_);
    for (int i = 0; i < 6; i++)
        nextRoom->insert(efactory_->create());
    currentRoom_->createDoor(nextRoom, RIGHT);

    //treasure room
    currentRoom_ = firstRoom_;
    int treasureSite = rand()%(2*roomCount);
    for (int i = 0; i <= treasureSite/2; i++)
    {
        currentRoom_ = currentRoom_->rooms_.at(RIGHT);
    }
    nextRoom = new Room(bunny_, TREASURE, ifactory_, pfactory_);
    nextRoom->insert(ifactory_->create(TREASURE));
    if (treasureSite%2 == 0)
    {
        currentRoom_->createDoor(nextRoom, UP);
    }
    else
    {
        currentRoom_->createDoor(nextRoom, DOWN);
    }

    //shop
    currentRoom_ = firstRoom_;
    int shopSite;
    do
    {
        shopSite = rand()%(2*roomCount);
    } while (shopSite == treasureSite);
    for (int i = 0; i <= shopSite/2; i++)
    {
        currentRoom_ = currentRoom_->rooms_.at(RIGHT);
    }
    nextRoom = new Room(bunny_, SHOP, ifactory_, pfactory_);
    nextRoom->insert(ifactory_->create(SHOP));
    nextRoom->insert(pfactory_->create(SHOP));

    if (shopSite%2 == 0)
    {
        currentRoom_->createDoor(nextRoom, UP);
    }
    else
    {
        currentRoom_->createDoor(nextRoom, DOWN);
    }
    //bonus room
    currentRoom_ = firstRoom_;
    int bonusSite;
    do
    {
        bonusSite = rand()%(2*roomCount);
    } while (bonusSite == treasureSite || bonusSite == shopSite);
    for (int i = 0; i <= bonusSite/2; i++)
    {
        currentRoom_ = currentRoom_->rooms_.at(RIGHT);
    }
    nextRoom = new Room(bunny_, BONUS, ifactory_, pfactory_);
    if (rand()%2 == 0)
    {
        if (rand()%4 == 0)
            nextRoom->insert(ifactory_->create(BONUS));
        else
            nextRoom->insert(pfactory_->create(BONUS));
    }
    if (bonusSite%2 == 0)
    {
        currentRoom_->createDoor(nextRoom, UP);
    }
    else
    {
        currentRoom_->createDoor(nextRoom, DOWN);
    }
    currentRoom_ = firstRoom_;
}

void Level::dispatchEvent(ALLEGRO_EVENT* event)
{
    if (event->type == ALLEGRO_EVENT_TIMER)
    {
        if (bunny_->atDoor_ >= 0)
        {
            enter(currentRoom_->rooms_.at(bunny_->atDoor_));
        }
        if (bunny_->atPortal_)
        {
            bunny_->atPortal_ = false;
            nextLevel();
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
