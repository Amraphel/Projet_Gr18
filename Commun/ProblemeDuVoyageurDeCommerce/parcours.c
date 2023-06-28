#ifndef PARCOURS
#define PARCOURS
#include "parcours.h"
#endif

//METTRE A JOUR LES DISTANCES AVEC LES POIDS

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
        poids.valeur = malloc(sizeof(int) * nbNoeud);
        poids.dest = malloc(sizeof(int) * nbNoeud);
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

parcours_t *parcoursGraphe(int **poids, double **phero, int nbNoeud)
{
    int numAct = 0;
    int *sommetTraverse = malloc(sizeof(int) * nbNoeud);
    int i;
    for (i = 0; i < nbNoeud; i++)
    {
        sommetTraverse[i] = 0;
    }
    sommetTraverse[0] = 1;

    poids_t *listePoid = creerPoids(poids, phero, nbNoeud);

    parcours_t *parcours = NULL;
    parcours_t **courant = &parcours;
    while (sommetTousTrav(sommetTraverse, nbNoeud) == 0 || numAct != 0)
    {
        int poidTotal = 0;
        for (i = 0; i < listePoid[numAct].nbPoids; i++)
        {
            poidTotal += listePoid[numAct].valeur[i] + 1;
        }
        float valDest = rand() % poidTotal + 1;
        int dest = 0;
        int k = 0;
        while (valDest > 0)
        {
            valDest = valDest - (listePoid[numAct].valeur[k] + 1);
            dest++;
            k++;
        }
        dest--;
        liaison_t lien;
        lien.dep = numAct;
        lien.arr = listePoid[numAct].dest[dest];
        parcours_t *act = malloc(sizeof(parcours_t));
        act->suiv = NULL;
        (*courant) = act;
        (*courant)->act = lien;
        courant = &(*courant)->suiv;
        numAct = listePoid[numAct].dest[dest];
        sommetTraverse[numAct] = 1;
    }
    free(sommetTraverse);
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

double **updatePhero(int taille, parcours_t *parcours, double puissancePhero, double coefAtt)
{
    double **tabPhero = initPhero(taille);
    int longueurMax = longParcours(parcours);
    parcours_t **courant = &parcours;
    int longueurAct = longueurMax;

    while ((*courant))
    {
        liaison_t lien = (*courant)->act;
        tabPhero[lien.dep][lien.arr] = (puissancePhero * coefAtt * longueurAct / longueurMax);
        courant = &(*courant)->suiv;
        longueurAct--;
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

void delParcours(parcours_t **parcours)
{
    if (*parcours)
    {
        parcours_t *cursor = *parcours;
        parcours_t *next = (*parcours)->suiv;
        while (next)
        {
            free(cursor);
            cursor = next;
            next = cursor->suiv;
        }

        free(parcours);
        parcours = NULL;
    }
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

int poidsParcours(parcours_t *parcours, int **tabPoids)
{

    int poidsTot = 0;

    parcours_t **courant = &parcours;

    while ((*courant))
    {
        liaison_t lien = (*courant)->act;
        poidsTot = poidsTot + tabPoids[lien.dep][lien.arr];
        courant = &(*courant)->suiv;
    }

    return poidsTot;
}

int fourmis(int **poids, int nbNoeud, double puissance, double coefAtt)
{
    double **phero = initPhero(nbNoeud);

    parcours_t **tabParcours = malloc(sizeof(parcours_t) * 100);
    int poidsFinal = -1;
    for (int k = 0; k < 100; k++)
    {
        for (int i = 0; i < 100; i++)
        {

            parcours_t *parcours = parcoursGraphe(poids, phero, nbNoeud);
            tabParcours[i] = parcours;
            int poidsParc = poidsParcours(parcours, poids);
            if (poidsFinal == -1 || poidsParc < poidsFinal)
            {
                poidsFinal = poidsParc;
            }
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
            double **pheroGen = updatePhero(nbNoeud, tabParcours[i], puissance, coefAtt);
            addMatrice(pheroGen, phero, nbNoeud);
            delPhero(pheroGen, nbNoeud);
        }
    }
    delPhero(phero, nbNoeud);
    delParcours(tabParcours);
    return poidsFinal;
}
