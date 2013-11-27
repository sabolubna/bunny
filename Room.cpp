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
        elements_.push_back(doors_[i]);
    }
    for (int i = 0; i < items_.size(); i++)
    {
        elements_.push_back(items_[i]);
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
    for (int i = 0; i < doors_.size(); i++)
    {
        if (bunny_->collidesWith(doors_[i]))
        {
            bunny_->handleCollision(doors_[i]);
        }
    }
    int i = 0;
    while (i < items_.size())
    {
        if (bunny_->collidesWith(items_[i]))
        {
            if (bunny_->handleCollision(items_[i]) == 1)
                items_.erase(items_.begin()+i);
        }
        i++;
    }
    bunny_->bounceFromWall(borders_);
}

void Room::insert(Item* item)
{
    items_.push_back(item);
}
