#include <math.h>

#include "bg_square.h"

// square position
float bg_square_x = 10;
float bg_square_y = 10;

// square velocity
float bg_square_dx = 2.5;
float bg_square_dy = 2.5;

// square rotation
float bg_square_theta = 0;
float bg_square_dtheta = 1;

// square radius
const int BG_SQUARE_SIZE = 200;

// square color list
const unsigned char BG_SQUARE_COLORS[] =
{
    255, 0, 0,
    0, 255, 0,
    0, 0, 255,
    255, 255, 255,
    255, 0, 255,
    0, 255, 255,
    255, 255, 0
};
const int BG_SQUARE_NUM_COLORS = sizeof(BG_SQUARE_COLORS) / sizeof(unsigned char);

// current color
int bg_square_cidx = 0;

void bg_square_draw(SDL_Renderer* sdl_rend)
{
    // get screen dims
    int width, height;
    SDL_GetRendererOutputSize(sdl_rend, &width, &height);

    SDL_SetRenderDrawColor(sdl_rend, 0, 0, 0, 255);
    SDL_RenderClear(sdl_rend);

    // draw square
    SDL_SetRenderDrawColor(
        sdl_rend,
        BG_SQUARE_COLORS[bg_square_cidx],
        BG_SQUARE_COLORS[bg_square_cidx + 1],
        BG_SQUARE_COLORS[bg_square_cidx + 2],
        255
    );
    for (float ti = 0; ti < 4; ti++)
    {
        float trad = (bg_square_theta + ti * 90) * (M_PI / 180);
        float tx = bg_square_x + cos(trad) * BG_SQUARE_SIZE;
        float ty = bg_square_y + sin(trad) * BG_SQUARE_SIZE;
        float nx = bg_square_x + cos(trad + M_PI / 2) * BG_SQUARE_SIZE;
        float ny = bg_square_y + sin(trad + M_PI / 2) * BG_SQUARE_SIZE;

        SDL_RenderDrawLine(sdl_rend, tx, ty, nx, ny);
    }

    SDL_RenderPresent(sdl_rend);

    // update square position
    bg_square_theta += bg_square_dtheta;

    bg_square_x += bg_square_dx;
    bg_square_y += bg_square_dy;

    // track whether we bounce so we can update the color
    int bounce = 0;

    if (bg_square_x < 0)
    {
        bg_square_x = 0;
        bg_square_dx = abs(bg_square_dx);
        bounce = 1;
    }
    if (bg_square_x > width)
    {
        bg_square_x = width;
        bg_square_dx = -abs(bg_square_dx);
        bounce = 1;
    }
    if (bg_square_y < 0)
    {
        bg_square_y = 0;
        bg_square_dy = abs(bg_square_dy);
        bounce = 1;
    }
    if (bg_square_y > height)
    {
        bg_square_y = height;
        bg_square_dy = -abs(bg_square_dy);
        bounce = 1;
    }

    if (bounce)
    {
        bg_square_cidx = (bg_square_cidx + 3) % BG_SQUARE_NUM_COLORS;
        bg_square_dtheta *= -1;
    }
}
