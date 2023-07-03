#ifndef BASE
#define BASE
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#endif
#include "regleIncly.h"

typedef enum
{
    NE,
    NO,
    SO,
    SE
} cadran_t;

typedef enum
{
    TL,
    L,
    AP,
    P,
    TP

} distance_t;

typedef enum
{
    JOKER = -1,
    MUR,
    VIDE,
    PACMAN
} case_t;