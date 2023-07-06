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
#ifndef PLATEAU
#define PLATEAU
#include "plateau.h"
#endif





typedef struct perso
{
    int id;
    int posX;
    int posY;
    int etat;
    int super;
    int coordX;
    int coordY;
}perso_t;

perso_t* initPac_man(int ** plateau, int w, int h);
int movePacman(int ** plateau, perso_t* Pac_man, int direction);
int movePacmanIA(int **plateau, perso_t *Pac_man);
void switchDirection(int direction, perso_t* Pac_man);