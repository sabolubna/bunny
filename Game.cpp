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

class AboutClickHandler : public Button::ClickHandler
{
    public:
        AboutClickHandler(Game* game): game_(game) {}
        void onClick()
        {
            game_->about();
        }
    private:
        Game* game_;
};

class BackClickHandler : public Button::ClickHandler
{
    public:
        BackClickHandler(Game* game): game_(game) {}
        void onClick()
        {
            game_->back();
        }
    private:
        Game* game_;
};

Game::Game()
{
    running_ = true;

    vector<Button> buttons;
    buttons.push_back(Button(new PlayClickHandler(this), 450, 150, 299, 54, 0, 0));
    buttons.push_back(Button(new AboutClickHandler(this), 450, 250, 299, 54, 0, 54));
    buttons.push_back(Button(new QuitClickHandler(this), 450, 350, 299, 54, 0, 108));
    mainmenu_ = new Menu(this, "pics/mainmenu.png", buttons);

    buttons.clear();
    buttons.push_back(Button(new ResumeClickHandler(this), 250, 250, 299, 54, 0, 162));
    buttons.push_back(Button(new EndGameClickHandler(this), 250, 350, 299, 54, 0, 108));
    pausemenu_ = new Menu(this, "pics/level02.bmp", buttons);

    buttons.clear();
    buttons.push_back(Button(new BackClickHandler(this), 550, 470, 132, 54, 0, 216));
    about_ = new Menu(this, "pics/about.png", buttons);

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

void Game::about()
{
    state_ = ABOUT;
    subgame_ = about_;
}

void Game::back()
{
    state_ = MENU;
    subgame_ = mainmenu_;
}
