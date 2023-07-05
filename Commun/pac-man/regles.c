#include "regles.h"
regles_t ** createMatRegles(int nbRegle)
{
    regles_t**matRegles = malloc(sizeof(regles_t *) *nbRegle);
    for (int i = 0; i < nbRegle; i++)
    {
        regles_t *ligne = malloc(sizeof(regles_t));
        matRegles[i] = ligne;
    }
    return matRegles;
}

regles_t **loadRegles(char* regles, int* valObj)
{
    int* nbRegle=malloc(sizeof(int));
    regles_t **matRegles = NULL;
    FILE *file = fopen(regles, "r");
    if (file)
    {
        fscanf(file, "%d %d\n", nbRegle, valObj);

        matRegles = createMatRegles(*nbRegle);
        
        for (int i = 0; i < *nbRegle; i++)
        {
            
            fscanf(file,"%d %d %d %d %d %d %d %d %d %d\n",(int*) (&(matRegles[i]->droite)),(int*) (&(matRegles[i]->haut)),(int*) (&(matRegles[i]->gauche))
                                                    ,(int*) (&(matRegles[i]->bas)),(int*) (&(matRegles[i]->distance_fantome)),(int*) (&(matRegles[i]->distance_pacman)),
                                                    (int*) (&(matRegles[i]->dir_fantome)),(int*) (&(matRegles[i]->dir_pacman)), (int*) (&(matRegles[i]->action)), (int*) (&(matRegles[i]->priorite)));
        }
    }
    free(nbRegle);
    nbRegle=NULL;
    fclose(file);
    return matRegles;
}


void ecrireRegle(regles_t ** matRegles,char* regles,int nbRegle, int valObj)
{
    FILE *file = fopen(regles, "w");
    if (file)
    {
        fprintf(file, "%d %d\n", nbRegle, valObj);

        for (int i = 0; i < nbRegle; i++)
        {
            fprintf(file,"%d %d %d %d %d %d %d %d %d %d\n",(matRegles[i]->droite),(matRegles[i]->haut),(matRegles[i]->gauche)
                                                    , (matRegles[i]->bas), (matRegles[i]->distance_fantome),(matRegles[i]->distance_pacman),
                                                    (matRegles[i]->dir_fantome), (matRegles[i]->dir_pacman), (matRegles[i]->action), (matRegles[i]->priorite));
        }
    }
    fclose(file);

}

int * initRegle(int nbRegle, int nbContrainte){
    int * reg= malloc(sizeof(int)*nbRegle*nbContrainte);
    for(int i =0; i<nbRegle*nbContrainte; i++){
        reg[i]=i;
    }
    return reg;
}


void shuffleRegle(int nbRegle, int nbContrainte, int * reg){
    for(int i=0; i <100; i++){
        int val1 = rand() %(nbRegle*nbContrainte);
        int val2 = rand() %(nbRegle*nbContrainte);
        int temp=reg[val1];
        reg[val1]=reg[val2];
        reg[val2]= temp;
    }
}