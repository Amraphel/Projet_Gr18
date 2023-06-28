#include "graphe.h"
#include <math.h>

int **initMatrice(int nombreDePoint)
{
    int **matrice = malloc(sizeof(int *) * nombreDePoint);
    if (matrice)
    {
        int i;
        int j;
        for (i = 0; i < nombreDePoint; i++)
        {
            int *mat = malloc(sizeof(int) * nombreDePoint);
            matrice[i] = mat;

            for (j = 0; j < nombreDePoint; j++)
            {
                matrice[i][j] = 0;
            }
        }
    }
    return matrice;
}

void generer(int **matrice, int inf, int sup)
{

    if (inf < sup)
    {
        int k = (rand() % (sup - inf + 1)) + inf;
        matrice[inf][inf + 1] = 1;
        matrice[inf + 1][inf] = 1;
        if (k + 1 <= sup)
        {
            matrice[inf][k + 1] = 1;
            matrice[k + 1][inf] = 1;
        }
        generer(matrice, inf + 1, k);
        generer(matrice, k + 1, sup);
    }
}

void genererGraphe(int **matrice, float p, int taillMatrice)
{

    for (int i = 0; i < taillMatrice; i++)
    {
        for (int j = i + 1; j < taillMatrice; j++)
        {
            float k = rand() / (RAND_MAX + 1.0);
            if (k < p)
            {
                matrice[i][j] = 1;
                matrice[i][j] = 1;
            }
        }
    }
}

cell_t *matToGraphe(int **matrice, int nbNoeud, point_t *tabPoint)
{
    int i;
    cell_t *graphe = malloc(sizeof(cell_t) * nbNoeud);
    for (i = 0; i < nbNoeud; i++)
    {
        cell_t noeud;
        noeud.point = tabPoint[i];
        noeud.lien = matrice[i];
        graphe[i] = noeud;
    }
    return graphe;
}

void matToPoids(int **matrice, int nbNoeud, point_t *tabPoint)
{
    int i;
    int j;
    for (i = 0; i < nbNoeud; i++)
    {
        for (j = 0; j < nbNoeud; j++)
        {
            if (matrice[i][j] == 1)
            {
                int distX = tabPoint[i].x - tabPoint[j].x;
                int distY = tabPoint[i].y - tabPoint[j].y;
                int poids = (int)hypot(distX, distY);
                matrice[i][j] = poids;
                matrice[j][i] = poids;
            }
        }
    }
}

void afficherMat(int **matrice, int nbNoeud)
{
    int i;
    int j;
    for (i = 0; i < nbNoeud; i++)
    {
        for (j = 0; j < nbNoeud; j++)
        {

            fprintf(stderr, "%d ", matrice[i][j]);
        }
        fprintf(stderr, "\n");
    }
}


void updateVisitable(int* tabType, cell_t* graphe,int nbNoeud, int numAct){
    for(int i=0; i<nbNoeud;i++){
        if(graphe[numAct].lien[i]>0){
            if(tabType[i]==0){
                tabType[i]=1;
            } else if (tabType[i]==2)
            {
                tabType[i]=3;
            }
        }

    }
}