#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <iostream>

class Room
{
    public:
        Room();
        Room(int ex, int up, int right, int down, int left);
        virtual ~Room();
        void createDoor(Room *that);
        int upborder, downborder, leftborder, rightborder;

    protected:
        Room *up;
        Room *right;
        Room *down;
        Room *left;
        int exit; //0 - up, 1 - right

    private:
};

#endif // ROOM_H
