#include "bg_party.h"

const char BG_PARTY_COLORS[] =
{
    0, 0, 0,
    0, 0, 255,
    0, 255, 0,
    0, 255, 255,
    255, 0, 0,
    255, 0, 255,
    255, 255, 0,
    255, 255, 255
};
const int BG_PARTY_NUM_COLORS = sizeof(BG_PARTY_COLORS) / sizeof(char);

// current color index
int bg_party_cidx = 0;

// frame countdown
int bg_party_count = BG_PARTY_STEP;

void bg_party_draw(SDL_Renderer* sdl_rend)
{
    SDL_SetRenderDrawColor(
        sdl_rend,
        BG_PARTY_COLORS[bg_party_cidx],
        BG_PARTY_COLORS[bg_party_cidx + 1],
        BG_PARTY_COLORS[bg_party_cidx + 2],
        255
    );
    SDL_RenderClear(sdl_rend);
    SDL_RenderPresent(sdl_rend);

    if (--bg_party_count < 0)
    {
        bg_party_count = BG_PARTY_STEP;
        bg_party_cidx = (bg_party_cidx + 3) % BG_PARTY_NUM_COLORS;
    }
}
