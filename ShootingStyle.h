#ifndef SHOOTINGSTYLE_H
#define SHOOTINGSTYLE_H

#include "Shot.h"
#include <vector>

class ShootingStyle
{
    public:
        virtual void freeze() = 0;
        virtual vector<Shot*> shoot() = 0;

    protected:
    private:
};

#endif // SHOOTINGSTYLE_H
