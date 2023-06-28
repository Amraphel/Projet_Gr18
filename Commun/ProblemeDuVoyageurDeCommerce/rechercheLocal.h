#ifndef PARCOURS
#define PARCOURS
#include "parcours.h"
#endif


poids_t *creerPoidsL(int **tabPoids, int nbNoeud);

int getOptiDest(poids_t* poids,int numAct);


int recherchelocal(int **poids, int nbNoeud, double probaRecuit);