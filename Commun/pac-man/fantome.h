#ifndef PERSO
#define PERSO
#include "perso.h"
#endif 

perso_t* initBlinky(int ** plateau, int w, int h);

void moveBlinky( // fonction blinky : plus court chemin vers pac-man
                SDL_Window *window,
                int** plateau, int w, int h, perso_t *Blinky, perso_t *Pac_man, SDL_Rect* rectBlin);

