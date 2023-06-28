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

int calcDist(int ** tabDist,int *ordreParc, int nbNoeud)
{
    int dist = 0;
    for (int i = 0; i < nbNoeud - 1; i++){
        dist+= tabDist[ordreParc[i]][ordreParc[i+1]];
    }
    return dist;
}

int parcours(int **poids, int nbNoeud, double temp)
{

    return 0;
}

int recherchelocal(int **poids, int nbNoeud, double probaRecuit)
{

    double temp = probaRecuit;
    int poidsTotal = -1;
    for (int i = 0; i < 100; i++)
    {
        int poidsParc = parcours(poids, nbNoeud, temp);

        if (poidsTotal == -1 || poidsParc < poidsTotal)
        {
            poidsTotal = poidsParc;
        }
        temp = temp * 0.99;
    }
    return poidsTotal;
}