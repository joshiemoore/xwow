/**
 * bg_party
 * Flashy colors.
 *
 * Joshua Moore 2020
 */
#ifndef BG_PARTY_H
#define BG_PARTY_H

#include <SDL2/SDL.h>

// number of frames between each color step
#define BG_PARTY_STEP 50

void bg_party_draw(SDL_Renderer* sdl_rend);

#endif
