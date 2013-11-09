// Autor: Sabina Jakubczak
//
// Opis programu: fajna gierka

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string>

#include "main.h"
#include "game.h"
#include "menu.h"


int main()
{
    bool playing = true;
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    ALLEGRO_DISPLAY *display = al_create_display(800,600);
    al_set_window_title(display,"Panda 3");
    Button *buttons;
    buttons = new Button[4];
    buttons[0] = Button(50, 50, 300, 50);
    buttons[1] = Button(50, 150, 300, 50);
    buttons[2] = Button(50, 250, 300, 50);
    buttons[3] = Button(50, 350, 300, 50);
    Menu menu = Menu("pics/mainmenu.jpg", buttons, 4);
    menu.view();
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if(!al_install_keyboard())
    {
        printf("failed to initialize keyboard!\n");
        return -1;
    }
    if(!al_install_mouse())
    {
        printf("failed to initialize mouse!\n");
        return -1;
    }
    al_register_event_source(queue, al_get_mouse_event_source());
    while (playing)
    //poruszanie sie po menu
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            cout << "down";
            int posx, posy;
            posx = event.mouse.x;
            posy = event.mouse.y;
            int click = menu.clicked(posx, posy);
            if (click >= 0)
            {
                printf("klik %d\n", click);
                switch (click)
                {
                    case 0:
                    {
                        Game game = Game();
                        game.play();
                        al_flush_event_queue(queue);
                        menu.view();
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
        /*jeœli play
            Game game = Game();
            game.Play();
        jesli kontynuuj
            FILE *fp = ("last.txt", "r");
            Game game = Game(fp);
            game.play();
        jesli instrukcje
            menu.howTo();
            while (1)
            {
                if (cofnij.klik) break;
            }
            menu.main();
        jesli quit
            playing = false;
        */
    }
    printf("udalo sie!");
    al_destroy_display(display);
    return 0;
}
