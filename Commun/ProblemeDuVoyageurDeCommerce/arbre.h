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