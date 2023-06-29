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

void play_with_texture_4(SDL_Texture *my_texture,
                         SDL_Window *window,
                         SDL_Renderer *renderer);



typedef struct perso
{
    int id;
    int posX;
    int posY;
}perso_t;

perso_t* initPac_man(int ** plateau);