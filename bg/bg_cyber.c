#include <math.h>

#include "bg_cyber.h"

// horizontal line offsets for "scrolling effect"
float cyber_offs = 0;

// horizontal position of the ship
int cyber_ship_x = 0;

void bg_cyber_draw(SDL_Renderer* sdl_rend)
{
    int width, height;
    SDL_GetRendererOutputSize(sdl_rend, &width, &height);

    SDL_SetRenderDrawColor(sdl_rend, 0, 0, 0, 255);
    SDL_RenderClear(sdl_rend);

    SDL_SetRenderDrawColor(sdl_rend, 255, 0, 255, 255);

    // draw horizon line
    SDL_RenderDrawLine(sdl_rend, 0, height / 2, width, height / 2);

    // draw horizontal lines
    float y = height / 2 - 20;
    float dy = 1;
    while (y <= height)
    {
        float ty = y + cyber_offs * (dy / 10);
        if (ty > height / 2)
        {
            SDL_RenderDrawLine(sdl_rend, 0, ty, width, ty);
        }

        y = y + dy;
        dy = dy + 5;
    }

    cyber_offs = cyber_offs + 0.1;
    if (cyber_offs > 10)
    {
        cyber_offs = 0;
    }

    // draw vertical lines
    for (int theta = 0; theta < 180; theta += 6)
    {
        float trad = theta * (M_PI / 180.0);
        SDL_RenderDrawLine(
            sdl_rend,
            width / 2,
            height / 2,
            width / 2 + cos(trad) * 2000,
            height / 2 + sin(trad) * 2000
        );
    }

    // draw sun
    for (int theta = 180; theta < 360; theta++)
    {
        float trad = theta * (M_PI / 180.0);
        SDL_RenderDrawLine(
            sdl_rend,
            width / 2,
            height / 2,
            width / 2 + cos(trad) * 150,
            height / 2 + sin(trad) * 150
        );
    }

    // draw "ship"
    int mx, my;
    SDL_GetGlobalMouseState(&mx, &my);

    cyber_ship_x = cyber_ship_x - (int)((cyber_ship_x - mx) / 50);

    float dx = (float)(cyber_ship_x) / width;

    float fx = width / 2 - cos(dx * M_PI) * 700;
    float fy = height / 2 + sin(dx * M_PI) * 300;

    float lx = width / 2 - cos((dx - 0.05) * M_PI) * 700;
    float ly = height / 2 + sin((dx - 0.1) * M_PI) * 500;

    float rx = width / 2 - cos((dx + 0.05) * M_PI) * 700;
    float ry = height / 2 + sin((dx + 0.1) * M_PI) * 500;

    SDL_SetRenderDrawColor(sdl_rend, 0, 255, 255, 255);

    SDL_RenderDrawLine(sdl_rend, fx, fy, lx, ly);
    SDL_RenderDrawLine(sdl_rend, lx, ly, rx, ry);
    SDL_RenderDrawLine(sdl_rend, rx, ry, fx, fy);
    

    SDL_RenderPresent(sdl_rend);
}
