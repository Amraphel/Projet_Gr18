#ifndef CLASSIQUE
#define CLASSIQUE
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#endif


typedef struct cell
{
    point_t point;
    int* lien;
}cell_t;
