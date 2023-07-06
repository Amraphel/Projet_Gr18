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
    int id; //numéro grace auquel on le repère dans la matrice
    int posX; //la ligne sur laquelle se trouve pac-man
    int posY; //la colonne sur laquelle se trouve pac-man
    int etat; //sens dans lequel pac-man est tourné
    int super; //indicateur qui donne si pac-Man est en mode super pac-man et si un fantome est mort
    int coordX; //ligne sur laquelle se trouve pac-man au début du jeu
    int coordY; //colonne sur laquelle se trouve pac-man au début du jeu
}perso_t;

perso_t* initPac_man(int ** plateau, int w, int h);
int movePacman(int ** plateau, perso_t* Pac_man, int direction);
int movePacmanIA(int **plateau, perso_t *Pac_man);
void switchDirection(int direction, perso_t* Pac_man);