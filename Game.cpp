#include "Game.h"
#include "Button.h"

class PlayClickHandler : public Button::ClickHandler
{
    public:
        PlayClickHandler(Game* game): game_(game) {}
        void onClick()
        {
            game_->play();
        }
    private:
        Game* game_;
};

class QuitClickHandler : public Button::ClickHandler
{
    public:
        QuitClickHandler(Game* game): game_(game) {}
        void onClick()
        {
            game_->quit();
        }
    private:
        Game* game_;
};

class ResumeClickHandler : public Button::ClickHandler
{
    public:
        ResumeClickHandler(Game* game): game_(game) {}
        void onClick()
        {
            game_->resume();
        }
    private:
        Game* game_;
};

class EndGameClickHandler : public Button::ClickHandler
{
    public:
        EndGameClickHandler(Game* game): game_(game) {}
        void onClick()
        {
            game_->endGame();
        }
    private:
        Game* game_;
};

Game::Game()
{
    running_ = true;

    vector<Button> buttons;
    buttons.push_back(Button(new PlayClickHandler(this), 450, 50, 300, 50));
    //buttons.push_back(Button(this, 50, 150, 300, 50));
    //buttons.push_back(Button(this, 50, 250, 300, 50));
    buttons.push_back(Button(new QuitClickHandler(this), 450, 350, 300, 50));
    mainmenu_ = new Menu(this, "pics/mainmenu.png", buttons);

    buttons.clear();
    buttons.push_back(Button(new ResumeClickHandler(this), 350, 150, 100, 50));
    buttons.push_back(Button(new EndGameClickHandler(this), 350, 250, 100, 50));
    //buttons.push_back(Button(this, 350, 350, 100, 50));
    //buttons.push_back(Button(this, 350, 450, 100, 50));
    pausemenu_ = new Menu(this, "pics/level02.bmp", buttons);

    subgame_ = mainmenu_;
    GameState state_ = MENU;
}

Game::~Game()
{
    //dtor
}

void Game::play()
{
    actualGame_ = new ActualGame(this);
    subgame_ = actualGame_;
}

void Game::quit()
{
    running_ = false;
}

bool Game::isRunning()
{
    return running_;
}

void Game::dispatchEvent(ALLEGRO_EVENT *event)
{
    subgame_->dispatchEvent(event);
}

void Game::onPause()
{
    state_ = PAUSE;
    subgame_ = pausemenu_;
}

void Game::resume()
{
    state_ = PLAYING;
    subgame_ = actualGame_;
}

void Game::endGame()
{
    //actualGame_->endGame();
    state_ = MENU;
    subgame_ = mainmenu_;
}
