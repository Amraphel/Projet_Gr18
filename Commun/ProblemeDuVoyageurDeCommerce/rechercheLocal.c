#include "rechercheLocal.h"


poids_t *creerPoidsL(int **tabPoids, int nbNoeud)
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
                poids.valeur[nbPoids] = tabPoids[i][j];
                nbPoids++;
            }
        }
        poids.nbPoids = nbPoids;
        listePoids[i] = poids;
    }
    return listePoids;
}

int parcours(int **poids, int nbNoeud, double temp){

    poids_t* listePoids = creerPoidsL(poids,nbNoeud);
    int numAct=0;
    int *sommetTraverse = malloc(sizeof(int) * nbNoeud);
    int i;
    for (i = 0; i < nbNoeud; i++)
    {
        sommetTraverse[i] = 0;
    }
    sommetTraverse[0] = 1;

    parcours_t *parcours = NULL;
    parcours_t **courant = &parcours;
    while (sommetTousTrav(sommetTraverse, nbNoeud) == 0 || numAct != 0)
    {
        
        int poidTotal = 0;
        for (i = 0; i < listePoids[numAct].nbPoids; i++)
        {
            poidTotal += listePoids[numAct].valeur[i] + 1;
        }
        float valDest = rand() % poidTotal +1;
        int dest = 0;
        int k=0;
        while (valDest > 0)
        {
            valDest = valDest- (listePoids[numAct].valeur[k] + 1);
            dest++;
            k++;
        }
        dest--;




        liaison_t lien;
        lien.dep = numAct;
        lien.arr = listePoids[numAct].dest[dest];
        parcours_t *act = malloc(sizeof(parcours_t));
        act->suiv=NULL;
        (*courant) = act;
        (*courant)->act = lien;
        courant = &(*courant)->suiv;
        numAct = listePoids[numAct].dest[dest];
        sommetTraverse[numAct] = 1;
    }
    return 0;
}


int recherchelocal(int **poids, int nbNoeud, double probaRecuit){

    double temp=probaRecuit;
    int poidsTotal=-1;
    for(int i=0; i<100; i++){
        int poidsParc = parcours(poids,nbNoeud, temp);

        if(poidsTotal==-1 ||poidsParc<poidsTotal){
            poidsTotal=poidsParc;
        }
        temp= temp*0.99;
    }
}