#ifndef ROOM_H
#define ROOM_H

#include "main.h"
#include <string>
#include <iostream>
#include <map>
#include "Element.h"
#include <vector>
#include <algorithm>
#include "Door.h"
#include "Bunny.h"
#include "Item.h"
#include "Shot.h"
#include "Pickup.h"
#include "Enemy.h"
#include "ItemFactory.h"
#include "PickupFactory.h"
#include "Portal.h"
#include "Bomb.h"

class Room : public RoomEffect
{
    public:
        Room(Bunny* bunny, SpaceItem* spaceItem, RoomType type, ItemFactory* ifactory, PickupFactory* pfactory);
        ~Room();
        void collectElements();
        void dispatchEvent(ALLEGRO_EVENT* event);
        void findCollisions();
        void onBombExplosion(Bomb* bomb);
        void createDoor(Room* that, Side side);
        void insert(Item* item);
        void insert(Pickup* pickup);
        void newPickup(PickupType type);
        void newPickup();
        void insert(Enemy* enemy);
        void leave();
        void enter();
        void draw();
        void oneRoomEffect(Effect effect, double change);
        int bunnyAtDoor_;
        map<int, Room*> rooms_;
        RoomType type_;
        double oneRoomEffect_[4];

    protected:
        int borders_[4];
        Bunny* bunny_;
        ALLEGRO_BITMAP *itempics_, *pickuppics_, *numbers_;
        vector<Element*> elements_;
        vector<Door*> doors_;
        vector<Item*> items_;
        vector<Shot*> shots_;
        vector<Pickup*> pickups_;
        vector<Enemy*> enemies_;
        vector<Portal*> portals_;
        vector<Bomb*> bombs_;
        ItemFactory* ifactory_;
        PickupFactory* pfactory_;
        SpaceItem* spaceItem_;

    private:
};

#endif // ROOM_H
