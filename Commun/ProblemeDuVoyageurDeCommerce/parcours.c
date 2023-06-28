#include "parcours.h"

poids_t *creerPoids(int **tabPoids, double **Phero, int nbNoeud)
{
    int i;
    int j;
    int nbPoids;
    poids_t *listePoids = malloc(sizeof(poids_t) * nbNoeud);
    for (i = 0; i < nbNoeud; i++)
    {
        nbPoids = 0;
        poids_t poids;
        poids.valeur = malloc(nbNoeud - 1);
        poids.dest = malloc(nbNoeud - 1);
        poids.nbPoids = nbPoids;
        for (j = 0; j < nbNoeud; j++)
        {
            if (tabPoids[i][j] > 0)
            {
                poids.dest[nbPoids] = j;
                poids.valeur[nbPoids] = Phero[i][j];
                nbPoids++;
            }
        }
        poids.nbPoids = nbPoids;
        listePoids[i] = poids;
    }
    return listePoids;
}

int sommetTousTrav(int *sommetTraverse, int nbNoeud)
{
    int res = 1;
    int i;
    for (i = 0; i < nbNoeud; i++)
    {
        res = res * sommetTraverse[i];
    }
    return res;
}

parcours_t *parcours(int **poids, double **phero, int nbNoeud)
{
    int numAct = 0;
    int *sommetTraverse = malloc(nbNoeud);
    int i;
    for (i = 0; i < nbNoeud; i++)
    {
        sommetTraverse[i] = 0;
    }
    sommetTraverse[0] = 1;

    poids_t *listePoid = creerPoids(poids, phero, nbNoeud);

    parcours_t *parcours = NULL;
    parcours_t **courant = &parcours;

    while (!sommetTousTrav(sommetTraverse, nbNoeud) && numAct != 0)
    {
        int poidTotal = 0;
        for (i = 0; i < listePoid[numAct].nbPoids; i++)
        {
            poidTotal += listePoid[numAct].valeur[i] + 1;
        }

        float valDest = rand() % poidTotal + 1;
        int dest = 0;
        while (valDest > 0)
        {
            valDest -= listePoid[numAct].valeur[i] + 1;
            dest++;
        }
        dest--;

        liaison_t lien;
        lien.dep = numAct;
        lien.arr = dest;
        (*courant)->act = lien;
        courant = &(*courant)->suiv;

        numAct = dest;
        sommetTraverse[numAct] = 1;
    }

    return parcours;
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

void updatePhero(double **tabPhero, parcours_t *parcours, double puissancePhero, double coefAtt)
{
    int longueurMax = longParcours(parcours);

    parcours_t **courant = &parcours;
    int longueurAct = longueurMax;

    while ((*courant))
    {
        liaison_t lien = (*courant)->act;
        tabPhero[lien.dep][lien.arr] = tabPhero[lien.dep][lien.arr] * (1 - coefAtt * longueurAct / longueurMax) + (puissancePhero * coefAtt * longueurAct / longueurMax);
        courant = &(*courant)->suiv;
        longueurAct--;
    }
}

double **initPhero(int taille)
{
    double **phero = malloc(sizeof(double *) * taille);
    if (phero)
    {
        for (int i = 0; i < taille; i++)
        {
            double *ligne = malloc(sizeof(double) * taille);
            if(ligne){
                for(int j=0; j<taille; j++){
                    ligne[j]=0;
                }
            }
            phero[i]=ligne;
        }
    }
    return phero;
}

void delPhero(double** phero, int taille)
{
    for(int i =0; i<taille; i++){
        free(phero[i]);
        phero[i]=NULL;
    }
    free(phero);
    phero=NULL;
}

void fourmis(int **poids, int nbNoeud, double puissance, double coefAtt)
{
    double ** phero = initPhero(nbNoeud);
    
    delPhero(phero, nbNoeud);
}