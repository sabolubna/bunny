#include "Room.h"

Room::Room(Bunny* bunny, RoomType type)
{
    type_ = type;
    borders_[UP] = 100;
    borders_[LEFT] = 50;
    borders_[RIGHT] = 750;
    borders_[DOWN] = 550;
    bunny_ = bunny;
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

    doors_.push_back(new Door(side, that->type_));
    rooms_.insert(pair<int, Room*>(side, that));
    that->doors_.push_back(new Door(side2, type_));
    that->rooms_.insert(pair<int, Room*>(side2, this));
}

bool compare(Element* x, Element* y)
{
    return x->posy_ < y->posy_;
}

void Room::draw()
{
    elements_.clear();
    elements_.push_back(bunny_);
    for (int i = 0; i < doors_.size(); i++)
    {
        doors_[i]->draw();
    }
    for (int i = 0; i < items_.size(); i++)
    {
        elements_.push_back(items_[i]);
    }
    for (int i = 0; i < shots_.size(); i++)
    {
        elements_.push_back(shots_[i]);
    }
    sort (elements_.begin(), elements_.end(), compare);
    for (int i = 0; i < elements_.size(); i++)
    {
        elements_[i]->draw();
    }
}

void Room::dispatchEvent(ALLEGRO_EVENT* event)
{
    if (event->type == ALLEGRO_EVENT_TIMER)
    {
        int i = 0;
        Shot* shot = bunny_->shoot();
        if (shot != NULL)
            shots_.push_back(shot);
        while (i < shots_.size())
        {
            shots_[i]->bounceFromWall(borders_);
            if (shots_[i]->range_ <= 0)
            {
                shots_.erase(shots_.begin()+i);
            }
            else
                i++;
        }
        draw();
        findCollisions();
    }
    for (int i = 0; i < elements_.size(); i++)
    {
        elements_[i]->dispatchEvent(event);
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
        if (bunny_->collidesWith(items_[i]))
        {
            if (bunny_->handleCollision(items_[i]) == 1)
                items_.erase(items_.begin()+i);
            else i++;
        }
        else
            i++;
    }

    i = 0;
    while (i < shots_.size())
    {
        if (bunny_->collidesWith(shots_[i]) && shots_[i]->hurtsBunny_)
        {
            bunny_->handleCollision(shots_[i]);
            shots_.erase(shots_.begin()+i);
        }
        else
            i++;
    }
    bunny_->bounceFromWall(borders_);
}

void Room::insert(Item* item)
{
    items_.push_back(item);
}

void Room::leave()
{
    shots_.clear();
}
