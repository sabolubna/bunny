#include "ActualGame.h"


using namespace std;

ActualGame::ActualGame(Delegate* delegate)
{
    delegate_ = delegate;
    level_ = new Level();
}

ActualGame::~ActualGame()
{
    //dtor
}

void ActualGame::dispatchEvent(ALLEGRO_EVENT *event)
{
    if (event->type == ALLEGRO_EVENT_TIMER)
    {
        if (!level_->playing_ || !level_->bunny_->alive())
        {
            delegate_->endGame();
            al_rest(1);
        }
        level_->dispatchEvent(event);
    }
    else if (event->type == ALLEGRO_EVENT_KEY_DOWN
        && event->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
    {
        delegate_->onPause();
    }
    else
    {
        level_->dispatchEvent(event);
    }
}

void ActualGame::draw()
{
    level_->draw();
}
