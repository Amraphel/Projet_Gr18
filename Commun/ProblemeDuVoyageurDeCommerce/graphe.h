#ifndef POINT
#define POINT
#include "point.h"
#endif


typedef struct cell
{
    point_t point;
    int* lien;
}cell_t;

int **initMatrice(int nombreDePoint);

void generer(int **matrice, int inf, int sup);

void genererGraphe(int **matrice, float p, int taillMatrice);

cell_t* matToGraphe(int ** matrice, int nbNoeud, point_t* tabPoint);

void matToPoids(int ** matrice, int nbNoeud, point_t* tabPoint);

void afficherMat(int **matrice, int nbNoeud);