#include "Level.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

Level::Level()
{

}

Level::Level(string nam, int x, int y, bool av, bool reqit[ITEM_CNT], int reqgr[GRADE_CNT], char background[16])
{
    name = nam;
    //button = Button(x, y, BUTTON, BUTTON);
    available = av;
    for (int i = 0; i < ITEM_CNT; i++)
        requireditems[i] = reqit[i];
    for (int i = 0; i < GRADE_CNT; i++)
        requiredgrades[i] = reqgr[i];
    this->background = al_load_bitmap(background);

}

Level::~Level()
{
    //dtor
}

void Level::viewInfo()
{
    cout << "kliknieto " << name << endl;
}

bool Level::clicked(int x, int y)
{
    if (button.clicked(x, y))
        return true;
    return false;
}

bool Level::unlocked()
{
    return available;
}

void Level::drawButton()
{
    if (available)
    {
        button.draw(al_map_rgb(0, 255, 0));
    }
    else
    {
        button.draw(al_map_rgb(255, 0, 0));
    }
}

void Level::drawScreen()
{
    al_draw_bitmap(background, 0, 0, 0);
}
