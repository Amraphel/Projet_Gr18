#ifndef PERSO
#define PERSO
#include "perso.h"
#endif 

perso_t* initBlinky(int ** plateau, int w, int h);
void moveBlinky(SDL_Texture *my_texture,     //fonction blinky : plus court chemin vers pac-man
                         SDL_Window *window,
                         SDL_Renderer *renderer);