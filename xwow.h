/**
 * Definitions for xwow, and inclusion of background modules.
 *
 * Joshua Moore 2020
 */

#ifndef XWOW_H
#define XWOW_H

#include <stdlib.h>




// ******* USER CONFIG ******* //

// random background interval
// set this to a non-zero number of seconds to randomize the background
// at this interval
#define XWOW_RAND_RATE 0

// *************************** //




// xwow framerate
#define XWOW_FPS 100

#include "bg/bg_corners.h"
#include "bg/bg_fade.h"
#include "bg/bg_cyber.h"
#include "bg/bg_square.h"
#include "bg/bg_party.h"

// main array of pointers to background draw functions
const void* BG_RENDER_FUNCS[] =
{
    &bg_corners_draw,
    &bg_fade_draw,
    &bg_cyber_draw,
    &bg_square_draw,
    &bg_party_draw
};

// total number of backgrounds in the array
const int BG_COUNT = sizeof(BG_RENDER_FUNCS) / sizeof(void*);

#endif
