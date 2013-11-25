#ifndef DELEGATE_H
#define DELEGATE_H


class Delegate
{
    public:
        virtual void onPause() = 0;
        virtual void resume() = 0;
    protected:
    private:
};

#endif // DELEGATE_H
