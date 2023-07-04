#ifndef PERSO
#define PERSO
#include "perso.h"
#endif 

perso_t* initBlinky(int ** plateau, int w, int h);

int moveBlinky( // fonction blinky : plus court chemin vers pac-man
                SDL_Window *window,
                int** plateau, int w, int h, perso_t *Blinky, perso_t *Pac_man, SDL_Rect* rectBlin, int* mort);
                
perso_t *initClyde(int **plateau, int w, int h);
int moveClyde(SDL_Window *window, int **plateau, int w, int h, perso_t *Clyde, perso_t *Pac_man, SDL_Rect *rectClyde, int *mort);

perso_t *initInky(int **plateau, int w, int h);
perso_t *initPinky(int **plateau, int w, int h);
int **heuristique(int **plateau, int pacX, int pacY, int w, int h);