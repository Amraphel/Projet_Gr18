#ifndef CLASSIQUE
#define CLASSIQUE
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "point.h"
#endif


typedef struct cell
{
    point_t point;
    int* lien;
}cell_t;

int **initMatrice(int nombreDePoint);

void generer(int **matrice, int inf, int sup);