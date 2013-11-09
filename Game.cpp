#include "Game.h"

Game::Game()
// creates new game
{
    panda = Panda();
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    Button *buttons;
    buttons = new Button[4];
    buttons[0] = Button(350, 150, 100, 50);
    buttons[1] = Button(350, 250, 100, 50);
    buttons[2] = Button(350, 350, 100, 50);
    buttons[3] = Button(350, 450, 100, 50);
    pausemenu = Menu("pics/level02.bmp", buttons, 4);
    time = 0;
    date = 1;
    hp = 10;
    hearts = 5;
    state = 0;
    map = al_load_bitmap("pics/map.png");
    std::fstream fp;
    fp.open( "files/levels.txt", std::ios::in);
    if(!fp.good())
        cout << "Problem z dostepem do pliku levels.txt" << std::endl;
    for (int i = 0; i < LVL_CNT; i++)
    {
        string name;
        fp >> name;
        int x, y;
        fp >> x;
        fp >> y;
        bool av, reqit[ITEM_CNT];
        fp >> av;
        for (int j = 0; j < ITEM_CNT; j++)
            fp >> reqit[j];
        int reqgr[GRADE_CNT];
        for (int j = 0; j < GRADE_CNT; j++)
            fp >> reqgr[j];
        char backgr[11];
        fp >> backgr;
        levels[i] = Level(name, x, y, av, reqit, reqgr, backgr);
    }
    fp.close();
    currentlvl = NULL;
}

Game::Game(int fp)
{

}

Game::~Game()
{
    //dtor
}

void Game::timePass()
{
    time+=1;
    if (time == MAX_TIME)
    {
        time = 0;
        date++;
    }
    return;
}

void Game::dayPass()
{
    time = 0;
    date++;
}

void Game::screen()
{
    switch(state)
    {
        case 0:
        {
            al_draw_bitmap(map, 0, 0, 0);
            for (int i = 0; i < LVL_CNT; i++)
            {
                levels[i].drawButton();
            }
            if (currentlvl != NULL)
                currentlvl->viewInfo();
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
