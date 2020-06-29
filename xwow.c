#include <X11/Xlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "xwow.h"

Display* x_disp;
Window x_root;

SDL_Window* sdl_win;
SDL_Renderer* sdl_rend;

// pointer to our background-rendering function
// this is called every frame
void (*xwow_render)(SDL_Renderer*);

int main()
{
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

    // lastly, get our SDL renderer
    if (!(sdl_rend = SDL_CreateRenderer(sdl_win, -1, 0)))
    {
        fprintf(stderr, "xwow: failed to create SDL renderer\n");
        exit(1);
    }

    xwow_render = &bg_cyber_draw;

    SDL_Event evt;

    while (1)
    {
        SDL_Delay(10);
        SDL_PollEvent(&evt);

        switch (evt.type)
        {
            case SDL_QUIT:
                goto cleanup;
                break;
        }

        // draw the background
        xwow_render(sdl_rend);
    }

    cleanup:
        // TODO: exit hotkey
        SDL_DestroyRenderer(sdl_rend);
        SDL_DestroyWindow(sdl_win);
        SDL_Quit();

        XCloseDisplay(x_disp);
}
