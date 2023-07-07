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
#include <threads.h>
#endif

// 2 -> gauche du coup 2
// 3 -> bas du coup 1
typedef enum
{
    JOKERc = -1,
    N,
    E,
    S,
    O
} cadran_t;

typedef enum
{
    JOKERd = -1,
    TL,
    L,
    AP,
    P,
    TP

} distance_t;

typedef enum
{
    JOKERca = -1,
    MUR,
    VIDE,
    PACMAN,
    FANTOME
} case_t;

typedef enum
{
    DROITE = 1 ,
    HAUT,
    GAUCHE,
    BAS
}action_t;

typedef struct
{
    case_t droite, haut, gauche, bas;       // le contenu des 4 cases voisines
    distance_t distance_fantome;           // dans quelle direction se trouve le fantome le plus proche
    distance_t distance_pacman;           // dans quelle direction se trouve pacman la plus proche
    cadran_t dir_fantome;             // dans quel cadran se trouve le fantome le plus proche
    cadran_t dir_pacman;             // dans quel cadran se trouve pacman
    action_t action;                  // quelle action doit être prise
    int priorite;                      // de 0 à 5
}regles_t;

void modifRegle(regles_t *regle, int numContrainte, int valeur);
void initCerveau(regles_t** tabRegle,int nbRegle);
void freeCerveau(regles_t** tabRegle, int nbRegle);
int *createListePos(int nbPos, int numContrainte);

int possibilite(int nbContrainte);
void freeHeuri(int **heuri, int w);