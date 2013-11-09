#ifndef PANDA_H
#define PANDA_H

#include "Element.h"
#include "Room.h"


class Panda : public Element
{
    public:
        Panda();
        ~Panda();
        void changePos(int x, int y, int z);
        void draw();

    protected:

    private:
};

#endif // PANDA_H
