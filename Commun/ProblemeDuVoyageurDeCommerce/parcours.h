#ifndef GRAPHE
#define GRAPHE
#include "graphe.h"
#endif


typedef struct poids{
    float* valeur;
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


poids_t *creerPoids(int **tabPoids, double **Phero, int nbNoeud);

int sommetTousTrav(int *sommetTraverse, int nbNoeud);

int *parcoursGraphe(double **phero, int nbNoeud);

int longParcours(parcours_t *parcours);

double ** initPhero(int taille);

int **dist(int **tabPoids, int nbNoeud);
int *initOrdre(int nbNoeud, int croiss);
int calcDist(int **tabDist, int *ordreParc, int nbNoeud);

double **updatePhero(int ** dist,int nbNoeud, int *parcours, double puissancePhero, double coefAtt);

void delPhero(double **phero, int taille);

void delParcours(parcours_t **parcours);

void addMatrice(double **source, double **dest, int nbNoeud);

int poidsParcours(parcours_t *parcours, int **tabPoids);

int fourmis(int **poids, int nbNoeud, double puissance, double coefAtt);