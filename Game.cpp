#include "Game.h"
#include "Button.h"

class QuitClickHandler : public Button::ClickHandler
{
    public:
        QuitClickHandler(Game* game): game_(game) {}
        virtual void onClick() { game_->quit(); }
    private:
        Game* game_;
};

Game::Game()
{
    running_ = true;

    vector<Button> buttons;
    buttons.push_back(Button(new QuitClickHandler(this), 50, 50, 300, 50));
    //buttons.push_back(Button(this, 50, 150, 300, 50));
    //buttons.push_back(Button(this, 50, 250, 300, 50));
    //buttons.push_back(Button(this, 50, 350, 300, 50));
    mainmenu_ = new Menu("pics/mainmenu.jpg", buttons);
    mainmenu_->draw();

    buttons.clear();
    //buttons.push_back(Button(this, 350, 150, 100, 50));
    //buttons.push_back(Button(this, 350, 250, 100, 50));
    //buttons.push_back(Button(this, 350, 350, 100, 50));
    //buttons.push_back(Button(this, 350, 450, 100, 50));
    pausemenu_ = new Menu("pics/level02.bmp", buttons);

    subgame_ = mainmenu_;
    GameState state_ = MENU;
}

Game::~Game()
{
    //dtor
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
/*void Game::menuEvent(ALLEGRO_EVENT *event)
{
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {

            int click = menu.clicked(posx, posy);
            if (click >= 0)
            {
                switch (click)
                {
                    case 0:
                    {
                        state = PLAYING;
                        game.newGame();
                        break;
                    }
                    case 1:
                    {
                        //continue
                        break;
                    }
                    case 2:
                    {
                        //about
                        break;
                    }
                    case 3:
                    {
                        playing = false;
                        break;
                    }
                }
            }
        }
}

void Game::screen()
{
    switch(state)
    {
        case 0:
        {
            mainmenu.draw();
            break;
        }
        case 1:
        {
            currentlvl->drawScreen();
            //sort
            for (int i = 0; i < elements.size(); i++)
            {
                elements[i]->draw();
            }
            break;
        }
        case 2:
        {
            pause.draw();
            break;
        }
    }
    al_flip_display();
}

int Game::pause()
{
    bool paused = true;
    pausemenu.view();
    ALLEGRO_EVENT event;
    while (paused)
    {
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN
            && pausemenu.clicked(event.mouse.x, event.mouse.y) >= 0)
        {
            switch (pausemenu.clicked(event.mouse.x, event.mouse.y))
            {
                case 0:
                {
                    paused = false;
                    break;
                }
                case 1:
                {
                    //save
                    break;
                }
                case 2:
                {
                    //instr
                    break;
                }
                case 3:
                {
                    return -1;
                    break;
                }
            }
        }
    }
    return 0;
}

void Game::save()
{

}

void Game::fight()
{
    elements.push_back(&panda);
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer;
    timer = al_create_timer(1.0 / 60.0);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    ALLEGRO_KEYBOARD_STATE keyboard;
    bool playing  = true;
    Room room = Room(3, 100, 750, 550, 50);
    while (hp > 0 && playing)
    {
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            //szuka kolizji, jak znajdzie, to odbija

            for (int i = 0; i < elements.size(); i++)
            {
                elements[i]->move();
                elements[i]->wall(&room);
            }
            screen();
        }
        if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                al_stop_timer(timer);
                if (pause() == -1)
                {
                    playing = false;
                }
                else
                {
                    al_start_timer(timer);
                    screen();
                }
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_W)
            {
                panda.changeSpeed(0, -1);
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_D)
            {
                panda.changeSpeed(1, 0);
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_S)
            {
                panda.changeSpeed(0, 1);
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_A)
            {
                panda.changeSpeed(-1, 0);
            }
        }
        if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_W)
            {
                panda.changeSpeed(0, 1);
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_D)
            {
                panda.changeSpeed(-1, 0);
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_S)
            {
                panda.changeSpeed(0, -1);
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_A)
            {
                panda.changeSpeed(1, 0);
            }
        }
    }
    al_stop_timer(timer);
    al_unregister_event_source(queue, al_get_timer_event_source(timer));
}

void Game::play()
// wlasciwa gra
{
    ALLEGRO_EVENT event;
    screen();
    bool playing = true;

    Button buttons[2];
    buttons[0] = Button(600, 95, 138, 42);
    buttons[1] = Button(600, 450, 138, 42);
    while (hp > 0 && playing)
    {
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            int posx, posy;
            posx = event.mouse.x;
            posy = event.mouse.y;

            // new game
            if (currentlvl != NULL && buttons[0].clicked(posx, posy) && currentlvl->unlocked())
            {
                cout << "play lvl " << currentlvl->name << "!" << endl;
                state = 1;
                fight();
                state = 0;
                screen();
                al_flush_event_queue(queue);
            }

            // quit
            if (buttons[1].clicked(posx, posy))
                playing = false;

            // lvls
            for (int i = 0; i < LVL_CNT; i++)
            {
                if (levels[i].clicked(posx, posy))
                {
                    currentlvl = &levels[i];
                    screen();
                }
            }
        }
    }
    cout << "end play" << endl;
    al_destroy_event_queue(queue);
}
*/
