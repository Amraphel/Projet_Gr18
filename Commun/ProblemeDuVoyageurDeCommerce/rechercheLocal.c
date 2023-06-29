#include "rechercheLocal.h"

int **dist(int **tabPoids, int nbNoeud)
{
    int **dist = initMatrice(nbNoeud);
    for (int i = 0; i < nbNoeud; i++)
    {
        for (int j = 0; j < nbNoeud; j++)
        {
            if (i != j && tabPoids[i][j] == 0)
            {
                dist[i][j] = -1;
            }
            else
            {
                dist[i][j] = tabPoids[i][j];
            }
        }
    }
    for (int i = 0; i < nbNoeud; i++)
    {
        for (int j = 0; j < nbNoeud; j++)
        {
            if (dist[i][j] == -1)
            {
                dist[i][j] = 9999999;
            }
            for (int k = 0; k < nbNoeud; k++)
            {
                if (dist[i][k] != -1 && dist[k][j] != -1 && dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}

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

int calcDist(int **tabDist, int *ordreParc, int nbNoeud)
{
    int dist = 0;
    for (int i = 0; i < nbNoeud - 1; i++)
    {
        dist += tabDist[ordreParc[i]][ordreParc[i + 1]];
    }
    dist += tabDist[ordreParc[nbNoeud - 1]][ordreParc[0]];
    return dist;
}

int *initOrdre(int nbNoeud)
{
    int *ordre = malloc(sizeof(int) * nbNoeud);
    for (int i = 0; i < nbNoeud; i++)
    {
        ordre[i] = i;
    }
    return ordre;
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
    int *ordre = initOrdre(nbNoeud);
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