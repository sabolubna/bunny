#ifndef BUTTON_H
#define BUTTON_H

#include <allegro5/allegro_primitives.h>

class Button
{
    public:
        Button();
        Button(int x, int y, int h, int w);
        virtual ~Button();
        bool clicked(int x, int y);
        void draw(ALLEGRO_COLOR color);

    protected:
        int posx, posy, height, width;

    private:
};

#endif // BUTTON_H