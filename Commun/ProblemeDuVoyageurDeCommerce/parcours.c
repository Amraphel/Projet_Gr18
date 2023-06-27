#include "parcours.h"

poids_t *creerPoid(int **tabPoids, int ** Phero, int nbNoeud)
{
    int nbPos = 0;
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

parcours_t* parcours(cell_t *graphes, int **poids, int nbNoeud)
{
    cell_t depart = graphes[0];
    int numAct = 0;
    int *sommetTraverse = malloc(nbNoeud);
    int i;
    for (i = 0; i < nbNoeud; i++)
    {
        sommetTraverse[i] = 0;
    }
    sommetTraverse[0] = 1;

    poids_t* listePoid= creerPoid(poids,nbNoeud);

    parcours_t * parcours= NULL;
    parcours_t ** courant = &parcours;

    while (!sommetTousTrav(sommetTraverse, nbNoeud) && numAct!=0)
    {
        int poidTotal = 0;
        for(i=0; i<listePoid[numAct].nbPoids; i++){
            poidTotal+= listePoid[numAct].valeur[i]+1;
        }

        int valDest= rand() % poidTotal + 1;
        int dest=0;
        while(valDest>0){
            valDest-= listePoid[numAct].valeur[i]+1;
            dest++;
        }
        dest--;

        liaison_t lien;
        lien.dep=numAct;
        lien.arr= dest;
        (*courant)->act=lien;
        courant=&(*courant)->suiv;

        numAct=dest;
        sommetTraverse[numAct]=1;

    }

    return parcours;
}

int longParcours(parcours_t * parcours){
    parcours_t** courant= &parcours;
    int longueur = 0;

    while((*courant)){
        longueur++;
        courant=&(*courant)->suiv;
    }
}

void updatePhero(int** tabPhero, parcours_t* parcours, double puissancePhero, double coefAtt){
    int longueurMax = longParcours(parcours);

    parcours_t** courant= &parcours;
    int longueurAct = longueurMax;

    while((*courant)){
        liaison_t lien = (*courant)->act;
        tabPhero[lien.dep][lien.arr]= tabPhero[lien.dep][lien.arr] * (1-coefAtt*longueurAct/longueurMax) + (puissancePhero*coefAtt*longueurAct/longueurMax);
        courant=&(*courant)->suiv;
        longueurAct--;
    }
}