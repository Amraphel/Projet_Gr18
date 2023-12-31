#ifndef PERSO
#define PERSO
#include "perso.h"
#endif 
#ifndef REGLE
#define REGLE
#include "calculRegle.h"
#endif
perso_t* initBlinky(int ** plateau, int w, int h);

int moveBlinky( // fonction blinky : plus court chemin vers pac-man
                SDL_Window *window,
                int** plateau, int w, int h, perso_t *Blinky, perso_t *Pac_man);
                
perso_t *initClyde(int **plateau, int w, int h);
int moveClyde(SDL_Window *window, int **plateau, int w, int h, perso_t *Clyde, perso_t *Pac_man);
perso_t *initInky(int **plateau, int w, int h);
int moveInky(SDL_Window *window, int **plateau, int w, int h, perso_t* Inky, perso_t *Pac_man);
perso_t *initPinky(int **plateau, int w, int h);
int movePinky(SDL_Window *window, int **plateau, int w, int h, perso_t* Pinky, perso_t *Pac_man);
void reapparitionFantome(int* tempsMortFantome, perso_t** tabPerso, int nbFan, SDL_Rect **rectFan, int* dir, int** plateau);
int **heuristique(int **plateau, int pacX, int pacY, int w, int h);
int* initTabTempsMortFantome(int nbFan);
perso_t *initFantome(int **plateau, int w, int h, int id);
int movePersoRegle(regles_t** regle, int ** plateau,perso_t** tabPerso, int idFant, int NBREGLE, double S, int w);