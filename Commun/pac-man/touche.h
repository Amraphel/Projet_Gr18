#ifndef PLATEAU
#define PLATEAU
#include "plateau.h"
#endif
#ifndef PERSO
#define PERSO
#include "perso.h"
#endif 
#ifndef AFFICHAGE
#define AFFICHAGE
#include "affichage.h"
#endif

int deplacement(int move, perso_t* Pac_man, int** plateau, SDL_Rect ** tabRectPerso, perso_t** tabPerso, int nbFan, SDL_Rect rectPac, int w, int h, int pause, int keyPressed);
int enPause(int pause);