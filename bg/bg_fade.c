#include "bg_fade.h"

// state variables
unsigned short bg_fade_r = 0;
unsigned short bg_fade_g = 0;
unsigned short bg_fade_b = 0;
int bg_fade_step = 1;

void bg_fade_draw(SDL_Renderer* sdl_rend)
{
    // fill with current color
    SDL_SetRenderDrawColor(
        sdl_rend,
        bg_fade_r,
        bg_fade_g,
        bg_fade_b,
        255
    );
    SDL_RenderClear(sdl_rend);
    SDL_RenderPresent(sdl_rend);

    // update color
    if (bg_fade_step > 0)
    {
        if (bg_fade_r < 255)
            bg_fade_r += bg_fade_step;
        else if (bg_fade_g < 255)
            bg_fade_g += bg_fade_step;
        else if (bg_fade_b < 255)
            bg_fade_b += bg_fade_step;
        else
            bg_fade_step = -bg_fade_step;
    }
    else if (bg_fade_step < 0)
    {
        if (bg_fade_r > 0)
            bg_fade_r += bg_fade_step;
        else if (bg_fade_g > 0)
            bg_fade_g += bg_fade_step;
        else if (bg_fade_b > 0)
            bg_fade_b += bg_fade_step;
        else
            bg_fade_step = -bg_fade_step;
    }
}
