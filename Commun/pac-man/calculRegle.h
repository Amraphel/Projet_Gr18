#ifndef REGLEF
#define REGLEF
#include "regleInky.h"
#endif
#ifndef PERSO
#define PERSO
#include "perso.h"
#endif
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
#ifndef REGLES
#define REGLES
#include "regles.h"
#endif
#include "fantome.h"

typedef struct param{
    int id;
    int * valSortie;
    regles_t ** listeRegle;
}param_t;


int testParcours(regles_t **tabRegle,int nbRegle, perso_t** tabPerso, int ** plateau, int w, int h, double s);
int recuit(int NBREGLE, char * source, char * dest);
int parcours( regles_t **tabRegle);