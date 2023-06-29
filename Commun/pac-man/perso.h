#ifndef BASE
#define BASE
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#endif
#include "plateau.h"

void mouv_Pac_Man(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, int direction ,int *posX, int *posY);



typedef struct perso
{
    int id;
    int posX;
    int posY;
    int etat;
}perso_t;

perso_t* initPac_man(int ** plateau, int w, int h);