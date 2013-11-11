#include "Panda.h"
#include <string>

using namespace std;

Panda::Panda()
{
    picture = al_load_bitmap("pics/Panda.jpg");
    al_convert_mask_to_alpha(picture, al_map_rgb(255,0,0));
    length = 70;
    width = 50;
    height = 75;
    posx = 50;
    posy = 300;
    posz = 0;
    step = 3;
    speedx = 0;
    speedy = 0;
}

Panda::~Panda()
{
    //dtor
}

void Panda::draw()
{
    al_draw_bitmap(picture, posx, posy - height, 0);
}

