#ifndef ROOM_H
#define ROOM_H

#include "main.h"
#include <string>
#include <iostream>
#include <map>
#include "Element.h"
#include <vector>
#include <algorithm>
#include <typeinfo>
#include "Door.h"
#include "Bunny.h"
#include "Item.h"
#include "Shot.h"
#include "Pickup.h"

class Room
{
    public:
        Room(Bunny* bunny, RoomType type);
        ~Room();
        void draw();
        void dispatchEvent(ALLEGRO_EVENT* event);
        void findCollisions();
        void createDoor(Room* that, Side side);
        void insert(Item* item);
        void insert(Pickup* pickup);
        void leave();
        int bunnyAtDoor_;
        map<int, Room*> rooms_;
        RoomType type_;

    protected:
        int borders_[4];
        Bunny* bunny_;
        vector<Element*> elements_;
        vector<Door*> doors_;
        vector<Item*> items_;
        vector<Shot*> shots_;
        vector<Pickup*> pickups_;

    private:
};

#endif // ROOM_H
