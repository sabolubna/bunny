#ifndef BUTTON_H
#define BUTTON_H

#include <allegro5/allegro_primitives.h>
#include "Delegate.h"

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
        Button(ClickHandler* handler, int x, int y, int h, int w);
        virtual ~Button();
        bool clicked(int x, int y);
        void draw(ALLEGRO_COLOR color);
        void onClick();

    protected:
        ClickHandler* handler_;
        int posx_, posy_, height_, width_;

    private:
};

#endif // BUTTON_H
