#ifndef LEVEL_H
#define LEVEL_H

#include "Button.h"
#include "main.h"
#include <string>

class Level
{
    public:
        string name;
        Level();
        Level(string nam, int x, int y, bool av, bool reqit[ITEM_CNT], int reqgr[GRADE_CNT],
              char background[16]);
        ~Level();
        void viewInfo();
        void drawButton();
        bool clicked(int x, int y);
        bool unlocked();
        void drawScreen();

    protected:
        //Room *firstroom;
        Button button;
        bool available;
        bool requireditems[ITEM_CNT];
        int requiredgrades[GRADE_CNT];
        ALLEGRO_BITMAP *background;

    private:
};

#endif // LEVEL_H
