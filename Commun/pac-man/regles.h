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
#ifndef REGLEF
#define REGLEF
#include "regleInky.h"
#endif

regles_t ** createMatRegles(int nbRegle);
regles_t **loadRegles(char* regles,int* nbRegle);
void ecrireRegle(regles_t ** matRegles,char* regles,int nbRegle);