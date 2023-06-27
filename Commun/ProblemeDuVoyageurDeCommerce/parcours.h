#ifndef ARBRE
#define ARBRES
#include "arbre.h"
#endif


typedef struct poids{
    int* valeur;
    int* dest;
    int nbPoids;
}poids_t;


typedef struct liaison{
    int dep;
    int arr;
} liaison_t;

typedef struct parcours{
    liaison_t act;
    struct parcours * suiv;
} parcours_t;