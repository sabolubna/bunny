#include "Room.h"

Room::Room()
{
    //Room(3, 150, 750, 550, 50);
}

Room::Room(int ex, int up, int right, int down, int left)
{
    exit = ex;
    upborder = up;
    rightborder = right;
    downborder = down;
    leftborder = left;
}

Room::~Room()
{
    //dtor
}
