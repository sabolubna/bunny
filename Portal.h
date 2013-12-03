#ifndef PORTAL_H
#define PORTAL_H

#include "Element.h"


class Portal : public Element
{
    public:
        Portal();
        ~Portal();
        void dispatchEvent(ALLEGRO_EVENT* event);
        void draw();
        bool locked_;

    protected:
        int animationState_;
        double animationTime_;
        double lastAnimation_;
};

#endif // PORTAL_H
