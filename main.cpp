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

int main()
{
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    ALLEGRO_DISPLAY *display = al_create_display(800,600);
    al_set_window_title(display,"The Bunny Story");
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if (!al_install_keyboard())
    {
        printf("failed to initialize keyboard!\n");
        return -1;
    }
    if (!al_install_mouse())
    {
        printf("failed to initialize mouse!\n");
        return -1;
    }
    ALLEGRO_TIMER *timer;
    timer = al_create_timer(1.0 / 60.0);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    Game game = Game();

    // main loop
    bool redraw;
    while (game.isRunning())
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        }
        if (redraw && al_is_event_queue_empty(queue))
        {
            game.draw();
            al_flip_display();
            //redraw = false;
        }
        game.dispatchEvent(&event);
    }

    printf("udalo sie!");
    al_destroy_display(display);
    return 0;
}
