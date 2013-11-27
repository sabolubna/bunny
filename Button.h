#ifndef BUTTON_H
#define BUTTON_H

#include <allegro5/allegro_primitives.h>

class Button
{
    public:
        class ClickHandler
        {
            public:
                virtual void onClick() = 0;
                virtual ~ClickHandler() {}
        };
        Button();
        Button(ClickHandler* handler, int x, int y, int width, int height, int picposx, int picposy);
        virtual ~Button();
        bool clicked(int x, int y);
        void draw(ALLEGRO_COLOR color);
        void onClick();

    protected:
        ClickHandler* handler_;
        int posx_, posy_, width_, height_;
        ALLEGRO_BITMAP* picture_;

    private:
};

#endif // BUTTON_H
