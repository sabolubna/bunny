#ifndef MOVINGSTYLE_H
#define MOVINGSTYLE_H


class MovingStyle
{
    public:
        void virtual move() = 0;
        void virtual bounceFromWall(Side side) = 0;
        void virtual freeze() = 0;
};



#endif // MOVINGSTYLE_H
