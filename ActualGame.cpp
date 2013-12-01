#include "ActualGame.h"


using namespace std;

ActualGame::ActualGame(Delegate* delegate)
{
    delegate_ = delegate;
    int r = rand()%LEVELTYPES;
    for (int i = 0; i < LEVELTYPES; i++)
        usedlevels_[i] = false;
    usedlevels_[r] = true;
    level_ = new Level(r);
    //level_->currentRoom_->enter();
}

ActualGame::~ActualGame()
{
    //dtor
}

void ActualGame::nextLevel()
{
    int r;
    do
    {
        r = rand()%LEVELTYPES;
    } while (usedlevels_[r]);
    usedlevels_[r] = true;
    level_ = new Level(r);
}

void ActualGame::dispatchEvent(ALLEGRO_EVENT *event)
{
    if (event->type == ALLEGRO_EVENT_TIMER)
    {
        if (!level_->bunny_->alive())
        {
            delegate_->endGame();
            al_rest(1);
        }
        level_->dispatchEvent(event);
        al_flip_display();
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
