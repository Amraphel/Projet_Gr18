#ifndef PARCOURS
#define PARCOURS
#include "parcours.h"
#endif

// METTRE A JOUR LES DISTANCES AVEC LES POIDS

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

int *initOrdre(int nbNoeud, int croiss)
{
    int *ordre = malloc(sizeof(int) * nbNoeud);
    for (int i = 0; i < nbNoeud; i++)
    {
        if (croiss == 1)
        {
            ordre[i] = i;
        }
        else
        {
            ordre[i] = -1;
        }
    }
    return ordre;
}

// poids_t *creerPoids(int **tabPoids, double **Phero, int nbNoeud)
// {
//     int i;
//     int j;
//     int nbPoids;
//     poids_t *listePoids = malloc(sizeof(poids_t) * nbNoeud);
//     for (i = 0; i < nbNoeud; i++)
//     {
//         nbPoids = 0;
//         poids_t poids;
//         poids.valeur = malloc(sizeof(int) * nbNoeud);
//         poids.dest = malloc(sizeof(int) * nbNoeud);
//         poids.nbPoids = nbPoids;
//         for (j = 0; j < nbNoeud; j++)
//         {
//             if (tabPoids[i][j] > 0)
//             {
//                 poids.dest[nbPoids] = j;
//                 poids.valeur[nbPoids] = Phero[i][j];
//                 nbPoids++;
//             }
//         }
//         poids.nbPoids = nbPoids;
//         listePoids[i] = poids;
//     }
//     return listePoids;
// }


int *parcoursGraphe(double **phero, int nbNoeud)
{
    int numAct = 0;
    int i;

    int *ordre = initOrdre(nbNoeud, 0);
    ordre[0] = 0;
    int *nonVis = initOrdre(nbNoeud, 1);
    nonVis[0] = -1;
    for (int k = 1; k < nbNoeud; k++)
    {
        int poidTotal = 0;
        for (i = 0; i < nbNoeud; i++)
        {
            if (nonVis[i] != -1)
            {
                poidTotal += phero[numAct][i] + 1;
            }
        }
        float valDest = rand() % poidTotal + 1;
        int dest = 0;
        while (valDest > 0)
        {
            if (nonVis[dest] != -1)
            {
                valDest = valDest - phero[numAct][i] - 1;
                
            }
            dest++;
        }
        dest--;
        nonVis[dest]=-1;
        ordre[k] = dest;
        numAct = dest;
    }
    return ordre;
}

int longParcours(parcours_t *parcours)
{
    parcours_t **courant = &parcours;
    int longueur = 0;
    while ((*courant))
    {
        longueur++;
        courant = &(*courant)->suiv;
    }
    return longueur;
}

double **initPhero(int taille)
{
    double **phero = malloc(sizeof(double *) * taille);
    if (phero)
    {
        for (int i = 0; i < taille; i++)
        {
            double *ligne = malloc(sizeof(double) * taille);
            if (ligne)
            {
                for (int j = 0; j < taille; j++)
                {
                    ligne[j] = 0;
                }
            }
            phero[i] = ligne;
        }
    }
    return phero;
}

double **updatePhero(int **dist, int nbNoeud, int *parcours, double puissancePhero, double coefAtt)
{
    double **tabPhero = initPhero(nbNoeud);
    int poidsMax = calcDist(dist, parcours, nbNoeud);
    int poidsAct = 1;
    for (int i = 0; i < nbNoeud - 1; i++)
    {

        tabPhero[parcours[i]][parcours[i + 1]] = (puissancePhero * coefAtt * poidsAct / poidsMax);
        poidsAct += dist[parcours[i]][parcours[i + 1]];
    }

    return tabPhero;
}

void delPhero(double **phero, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        free(phero[i]);
        phero[i] = NULL;
    }
    free(phero);
    phero = NULL;
}

void addMatrice(double **source, double **dest, int nbNoeud)
{
    for (int i = 0; i < nbNoeud; i++)
    {
        for (int j = 0; i < nbNoeud; i++)
        {
            dest[i][j] = dest[i][j] + source[i][j];
        }
    }
}

int fourmis(int **poids, int nbNoeud, double puissance, double coefAtt)
{
    int **tabDist = dist(poids, nbNoeud);
    double **phero = initPhero(nbNoeud);
    int **tabParc = malloc(sizeof(int *) * 100);
    int poidsFinal = -1;
    for (int k = 0; k < 100; k++)
    {
        for (int i = 0; i < 100; i++)
        {

            int* parcours = parcoursGraphe( phero, nbNoeud);
            int poidsParc= calcDist(tabDist,parcours,nbNoeud);
            if (poidsFinal == -1 || poidsParc < poidsFinal)
            {
                poidsFinal = poidsParc;
            }
            tabParc[i]=parcours;
        }

        for (int i = 0; i < nbNoeud; i++)
        {
            for (int j = 0; i < nbNoeud; i++)
            {
                phero[i][j] = phero[i][j] * (1 - coefAtt);
            }
        }

        for (int i = 0; i < 100; i++)
        {
            double **pheroGen = updatePhero(tabDist, nbNoeud, tabParc[i], puissance, coefAtt);
            addMatrice(pheroGen, phero, nbNoeud);
            delPhero(pheroGen, nbNoeud);
        }
    }
    delPhero(phero, nbNoeud);
    for(int i=0; i<nbNoeud; i++){
        free(tabParc[i]);
        tabParc[i]=NULL;
    }
    free(tabParc);
    return poidsFinal;
}
