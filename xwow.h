/**
 * Definitions for xwow, and inclusion of background modules.
 *
 * Joshua Moore 2020
 */

#ifndef XWOW_H
#define XWOW_H

#include <stdlib.h>

#include "bg/bg_corners.h"
#include "bg/bg_fade.h"
#include "bg/bg_cyber.h"

// main array of pointers to background draw functions
const void* BG_RENDER_FUNCS[] =
{
    &bg_corners_draw,
    &bg_fade_draw,
    &bg_cyber_draw
};

// total number of backgrounds in the array
const int BG_COUNT = sizeof(BG_RENDER_FUNCS) / sizeof(void*);

#endif
