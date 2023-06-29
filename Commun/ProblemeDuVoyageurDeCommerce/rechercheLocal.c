#include "rechercheLocal.h"



void printMat(int **mat, int nbNoeud)
{
    for (int i = 0; i < nbNoeud; i++)
    {
        for (int j = 0; j < nbNoeud; j++)
        {
            fprintf(stderr, "%d ", mat[i][j]);
        }
        fprintf(stderr, "\n");
    }
}



int *inv2Elem(int *ordre, int nbNoeud)
{
    int *ordre2 = malloc(sizeof(int) * nbNoeud);
    for (int i = 0; i < nbNoeud; i++)
    {
        ordre2[i] = ordre[i];
    }
    int elem1 = rand() % nbNoeud;
    int elem2 = rand() % nbNoeud;
    while (elem2 == elem1)
    {
        elem2 = rand() % nbNoeud;
    }
    int temp = ordre[elem1];
    ordre2[elem1] = ordre[elem2];
    ordre2[elem2] = temp;
    return ordre2;
}

int recherchelocal(int **poids, int nbNoeud, int init, double objectif)
{

    double temp = init;
    int *ordre = initOrdre(nbNoeud,1);
    int *ordre2 = NULL;
    int **tabDist = dist(poids, nbNoeud);
    int poidsTotal = calcDist(tabDist, ordre, nbNoeud);
    for (int i = 0; i < 100; i++)
    {
        int *ordre2 = inv2Elem(ordre, nbNoeud);
        int newPoids = calcDist(tabDist, ordre2, nbNoeud);
        if (newPoids < poidsTotal)
        {
            poidsTotal = newPoids;
            ordre = ordre2;
        }
        else
        {
            double prop = (float)rand() / RAND_MAX;
            if (prop < temp)
            {
                poidsTotal = newPoids;
                ordre = ordre2;
            }
        }
        temp = init * pow(sqrt(objectif / (init * 143)), 100);
    }
    free(ordre);
    if (ordre2)
    {
        free(ordre2);
    }

    return poidsTotal;
}