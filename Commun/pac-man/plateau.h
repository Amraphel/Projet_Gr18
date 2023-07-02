
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


int **loadPlateau(char *lvl, int*w, int* h);

void coordPlat(int **plateau,int w, int h, int val, int *x, int *y);

int movePossible(int** plateau, int xPerso, int yPerso, int direction);

void movePersoInPlateau(int ** plateau, int* xPerso, int* yPerso, int idPerso,int direction, int* mort);

void printPlateau(int **mat, int w, int h);

int gom_exist(int ** plateau, int w, int h);

void savePlateau(int ** plateau, int w, int h);