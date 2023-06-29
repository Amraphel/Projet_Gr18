
#ifndef BASE
#define BASE
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#endif


int **loadPlateau(char *lvl, int*w, int* h);

void coordPlat(int **plateau,int w, int h, int val, int *x, int *y);

void movePac_manInPlateau(int ** plateau, int* xPerso, int* yPerso, int direction);

int movePossible(int** plateau, int xPerso, int yPerso, int direction);

void printPlateau(int **mat, int w, int h);

int gom_exist(int ** plateau, int taille);