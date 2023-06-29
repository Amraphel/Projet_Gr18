
#ifndef BASE
#define BASE
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#endif

perso_t* initBlinky(int ** plateau, int w, int h);
int **loadPlateau(char *lvl, int*w, int* h);

void coordPlat(int **plateau,int w, int h, int val, int *x, int *y);

void movePersoInPlateau(int ** plateau, int* xPerso, int* yPerso, int wMaxPlateau, int hMaxPlateau, int direction);