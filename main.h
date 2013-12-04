#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define ITEM_CNT 10

#define LVL_CNT 2

enum GameState {MENU, PLAYING, PAUSE, ABOUT};

enum Side {LEFT, UP, RIGHT, DOWN};

enum RoomType {NORMAL = 0, BONUS = 2, TREASURE = 3, SECRET = 5, BOSS = 6};

enum PickupType {COIN, BOMB, KEY, CARROT};

using namespace std;

#endif // MAIN_H_INCLUDED
