#ifndef PARCOURS
#define PARCOURS
#include "parcours.h"
#endif
int **dist(int **tabPoids, int nbNoeud);
void printMat(int** mat, int nbNoeud);


int recherchelocal(int **poids, int nbNoeud, double probaRecuit);