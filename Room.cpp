#include "Room.h"

Room::Room(Bunny* bunny, RoomType type, ItemFactory* ifactory, PickupFactory* pfactory)
{
    type_ = type;
    borders_[UP] = 100;
    borders_[LEFT] = 50;
    borders_[RIGHT] = 750;
    borders_[DOWN] = 550;
    bunny_ = bunny;
    ifactory_ = ifactory;
    pfactory_ = pfactory;
}

Room::~Room()
{
    //dtor
}

void Room::createDoor(Room* that, Side side)
{
    //side2: RIGHT if side==LEFT, DOWN if side==UP etc
    int side2;
    if (side < 2) side2 = side + 2;
    else side2 = side - 2;

    if (type_ == BONUS || that->type_ == BONUS)
    {
        doors_.push_back(new Door(side, BONUS));
        rooms_.insert(pair<int, Room*>(side, that));
        that->doors_.push_back(new Door(side2, BONUS));
        that->rooms_.insert(pair<int, Room*>(side2, this));
        return;
    }
    doors_.push_back(new Door(side, that->type_));
    rooms_.insert(pair<int, Room*>(side, that));
    that->doors_.push_back(new Door(side2, type_));
    that->rooms_.insert(pair<int, Room*>(side2, this));
}

bool compare(Element* x, Element* y)
{
    return x->posy_ < y->posy_;
}

void Room::collectElements()
{
    elements_.clear();
    elements_.push_back(bunny_);
    for (int i = 0; i < items_.size(); i++)
    {
        elements_.push_back(items_[i]);
    }
    for (int i = 0; i < shots_.size(); i++)
    {
        elements_.push_back(shots_[i]);
    }
    for (int i = 0; i < pickups_.size(); i++)
    {
        elements_.push_back(pickups_[i]);
    }
    for (int i = 0; i < enemies_.size(); i++)
    {
        elements_.push_back(enemies_[i]);
    }
    sort(elements_.begin(), elements_.end(), compare);
}

void Room::dispatchEvent(ALLEGRO_EVENT* event)
{
    if (event->type == ALLEGRO_EVENT_TIMER)
    {
        Shot* shot = bunny_->shoot();
        if (shot != NULL)
            shots_.push_back(shot);

        for (int i = 0; i < enemies_.size(); i++)
        {
            vector<Shot*> shots = enemies_[i]->shoot();
            if (shots.size() > 0)
                for (int i = 0; i < shots.size(); i++)
                    shots_.push_back(shots[i]);
        }
        int i = 0;
        while (i < shots_.size())
        {
            shots_[i]->bounceFromWall(borders_);
            if (shots_[i]->range_ <= 0)
            {
                Shot* toDelete = shots_[i];
                shots_.erase(shots_.begin()+i);
                delete toDelete;
            }
            else
                i++;
        }
        findCollisions();
        collectElements();
        for (int i = 0; i < elements_.size(); i++)
        {
            elements_[i]->dispatchEvent(event);
        }
        for (int i = 0; i < portals_.size(); i++)
        {
            portals_[i]->dispatchEvent(event);
        }
    }
}

void Room::findCollisions()
{
    //collisions with doors
    for (int i = 0; i < doors_.size(); i++)
    {
        if (bunny_->collidesWith(doors_[i]))
        {
            bunny_->handleCollision(doors_[i]);
        }
    }
    //collisions with items
    int i = 0;
    while (i < items_.size())
    {
        if (bunny_->collidesWith(items_[i]) && items_[i]->lying())
        {
            if (items_[i]->handleCollision(bunny_, this))
            {
                Item* toDelete = items_[i];
                items_.erase(items_.begin()+i);
                delete toDelete;
            }
            else i++;
        }
        else
            i++;
    }
    //collisions with pickups
    i = 0;
    while (i < pickups_.size())
    {
        if (bunny_->collidesWith(pickups_[i]))
        {
            if (bunny_->handleCollision(pickups_[i]) == 1)
            {
                Pickup* toDelete = pickups_[i];
                pickups_.erase(pickups_.begin()+i);
                delete toDelete;
            }
            else i++;
        }
        else
            i++;
    }
    //collisions with enemies
    for (int i = 0; i < enemies_.size(); i++)
    {
        enemies_[i]->bounceFromWall(borders_);
        if (bunny_->collidesWith(enemies_[i]))
        {
            bunny_->hurt(1);
        }
    }
    //collisions with shots
    i = 0;
    while (i < shots_.size())
    {
        if (shots_[i]->hurtsBunny_)
        {
            if (bunny_->collidesWith(shots_[i]))
            {
                bunny_->hurt(shots_[i]->damage_);
                shots_.erase(shots_.begin()+i);
            }
            else
                i++;
        }
        else
        {
            int j = 0;
            while (j < enemies_.size())
            {
                if (enemies_[j]->collidesWith(shots_[i]))
                {
                    if (enemies_[j]->handleCollision(shots_[i]))
                    {
                        enemies_.erase(enemies_.begin()+j);
                        if (enemies_.size() == 0)
                        {
                            for (int k = 0; k < doors_.size(); k++)
                                doors_[k]->unlock();
                            if (type_ == BOSS)
                            {
                                printf("...\n");
                                insert(ifactory_->create(type_));
                                printf("...\n");
                                portals_.push_back(new Portal());
                                printf("...\n");
                            }
                            else
                                insert(pfactory_->create(type_));
                        }
                    }
                    shots_.erase(shots_.begin()+i);
                    i--;
                    break;
                }
                else
                    j++;
            }
            i++;
        }
    }
    //collisions with portals
    for (int i = 0; i < portals_.size(); i++)
    {
        if (bunny_->collidesWith(portals_[i]) && !portals_[i]->locked_)
        {
            bunny_->atPortal_ = true;
        }
        else
            portals_[i]->locked_ = false;
    }
    bunny_->bounceFromWall(borders_);
}

void Room::insert(Item* item)
{
    items_.push_back(item);
}

void Room::insert(Pickup* pickup)
{
    pickups_.push_back(pickup);
}

void Room::newPickup(PickupType ptype)
{
    pickups_.push_back(pfactory_->create(type_, ptype));
}

void Room::insert(Enemy* enemy)
{
    enemies_.push_back(enemy);
}

void Room::enter()
{
    if (enemies_.size() > 0)
        for (int i = 0; i < doors_.size(); i++)
            doors_[i]->lock();

    for (int i = 0; i < enemies_.size(); i++)
    {
        enemies_[i]->freeze();
    }
}

void Room::leave()
{
    shots_.clear();
}

void Room::draw()
{
    if (bunny_->spacePicture_ != NULL)
        al_draw_bitmap(bunny_->spacePicture_, 5, 5, 0);
    for (int i = 0; i < doors_.size(); i++)
    {
        doors_[i]->draw();
    }
    for (int i = 0; i < portals_.size(); i++)
    {
        portals_[i]->draw();
    }
    collectElements();
    for (int i = 0; i < elements_.size(); i++)
        elements_[i]->draw();
}
