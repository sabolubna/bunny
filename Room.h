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

class Room
{
    public:
        Room(Bunny* bunny, RoomType type);
        ~Room();
        void draw();
        void dispatchEvent(ALLEGRO_EVENT* event);
        void findCollisions();
        void createDoor(Room* that, Side side);
        void insert(Element* element);
        int bunnyAtDoor_;
        map<int, Room*> rooms_;
        RoomType type_;

    protected:
        int borders_[4];
        Bunny* bunny_;
        vector<Element*> elements_;
        vector<Door*> doors_;

    private:
};

#endif // ROOM_H
