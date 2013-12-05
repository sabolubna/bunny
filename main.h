#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define FIRSTSHOPITEM 6
#define LASTSHOPITEM 10
#define FIRSTUNIVERSALITEM 0
#define LASTUNIVERSALITEM 5

#define ITEM_CNT 10

#define LVL_CNT 2

enum GameState {MENU, PLAYING, PAUSE, ABOUT};

enum Side {LEFT, UP, RIGHT, DOWN};

enum RoomType {NORMAL = 0, SHOP = 1, BONUS = 2, TREASUREOPEN = 3, TREASURE = 4, SECRET = 5, BOSS = 6};

enum PickupType {COIN, BOMB, KEY, CARROT};

using namespace std;

#endif // MAIN_H_INCLUDED
