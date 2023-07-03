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
#include "plateau.h"





typedef struct perso
{
    int id;
    int posX;
    int posY;
    int etat;
}perso_t;

perso_t* initPac_man(int ** plateau, int w, int h);
int movePacman(int ** plateau, perso_t* Pac_man,int* mort, int direction, SDL_Rect* rectPac);
int movePacmanIA(int **plateau, perso_t *Pac_man);