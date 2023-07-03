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


typedef enum
{
    N,
    E,
    S,
    O
} cadran_t;

typedef enum
{
    TL,
    L,
    AP,
    P,
    TP

} distance_t;

typedef enum
{
    JOKER = -1,
    MUR,
    VIDE,
    PACMAN,
    FANTOME
} case_t;

typedef enum
{
    DROITE,
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
    int priorite;                      // de 0 à 5
    action_t action;                  // quelle action doit être prise
}regles_t;

void modifRegle(regles_t **tabRegle, int nbRegle, int nbContrainte);
regles_t** initCervau(int nbRegle, int nbContrainte);
void freeCerveau(regles_t** tabRegle, int nbRegle);