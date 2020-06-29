#include <X11/Xlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#include "xwow.h"

Display* x_disp;
Window x_root;

SDL_Window* sdl_win;
SDL_Renderer* sdl_rend;

// pointer to our background-rendering function
// this is called every frame
void (*xwow_render)(SDL_Renderer*);

// index in the render func array
int bg_idx = 0;

void cleanup(int d)
{
    SDL_DestroyRenderer(sdl_rend);
    SDL_DestroyWindow(sdl_win);
    SDL_Quit();

    XCloseDisplay(x_disp);

    exit(0);
}

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        fprintf(stderr, "Too many arguments.\n");
        fprintf(stderr, "Usage: xwow [id]\n");
        exit(1);
    }
    else if (argc == 2)
    {
        // user provided a background id
        bg_idx = atoi(argv[1]);
    }
    else
    {
        // user did not provide an id, pick random background
        srand(time(NULL));
        bg_idx = rand() % BG_COUNT;
    }

    // check for out of bounds
    if (bg_idx < 0 || bg_idx >= BG_COUNT)
    {
        fprintf(stderr, "ID must be in range 0-%d\n.", BG_COUNT - 1);
        exit(1);
    }

    // initialize X
    if (!(x_disp = XOpenDisplay(NULL)))
    {
        fprintf(stderr, "xwow: failed to open display\n");
        exit(1);
    }
    x_root = RootWindow(x_disp, DefaultScreen(x_disp));

    // initialize SDL to draw to root window
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "xwow: failed to init SDL\n");
        exit(1);
    }

    if (!(sdl_win = SDL_CreateWindowFrom((void *)x_root)))
    {
        fprintf(stderr, "xwow: failed to create SDL window\n");
        exit(1);
    }

    // get our SDL renderer
    if (!(sdl_rend = SDL_CreateRenderer(sdl_win, -1, 0)))
    {
        fprintf(stderr, "xwow: failed to create SDL renderer\n");
        exit(1);
    }

    signal(SIGINT, cleanup);

    xwow_render = BG_RENDER_FUNCS[bg_idx];

    while (1)
    {
        SDL_Delay(10);
        SDL_PollEvent(NULL);

        // draw the background
        xwow_render(sdl_rend);
    }
}
