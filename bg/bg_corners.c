#include "bg_corners.h"

void bg_corners_draw(SDL_Renderer* sdl_rend)
{
    // get screen dims
    int width, height;
    SDL_GetRendererOutputSize(sdl_rend, &width, &height);

    // get mouse position
    int mx, my;
    SDL_GetGlobalMouseState(&mx, &my);

    SDL_SetRenderDrawColor(sdl_rend, 0, 0, 0, 255);
    SDL_RenderClear(sdl_rend);

    SDL_SetRenderDrawColor(sdl_rend, 0, 0, 255, 255);

    // draw line from each corner
    SDL_RenderDrawLine(sdl_rend, 0, 0, mx, my);
    SDL_RenderDrawLine(sdl_rend, width, 0, mx, my);
    SDL_RenderDrawLine(sdl_rend, 0, height, mx, my);
    SDL_RenderDrawLine(sdl_rend, width, height, mx, my);

    SDL_RenderPresent(sdl_rend);
}
