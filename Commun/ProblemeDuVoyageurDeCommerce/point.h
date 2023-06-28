#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct point
{
    int x;
    int y;
}point_t;

point_t* tabPointAleatoire(int NombreDePoint, SDL_Window *window);
int* initTypeNoeud(int taille);