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

regles_t **loadRegles(char* regles,int* nbRegle)
{
    regles_t **matRegles = NULL;
    fprintf(stderr, "aled\n");
    FILE *file = fopen(regles, "r");
    fprintf(stderr, "aled\n");
    if (file)
    {
        fprintf(stderr, "nbregle = %d\n", *nbRegle);
        fscanf(file, "%d\n", nbRegle);
fprintf(stderr, "nbregle = %d\n", *nbRegle);
        matRegles = createMatRegles(*nbRegle);
        
        for (int i = 0; i < *nbRegle; i++)
        {
            
            fscanf(file,"%d %d %d %d %d %d %d %d %d %d\n",(int*) (&(matRegles[i]->droite)),(int*) (&(matRegles[i]->haut)),(int*) (&(matRegles[i]->gauche))
                                                    ,(int*) (&(matRegles[i]->bas)),(int*) (&(matRegles[i]->distance_fantome)),(int*) (&(matRegles[i]->dir_pacman)),
                                                    (int*) (&(matRegles[i]->dir_fantome)),(int*) (&(matRegles[i]->dir_pacman)), (int*) (&(matRegles[i]->action)), (int*) (&(matRegles[i]->priorite)));
        }
    }
    fclose(file);
    return matRegles;
}


void ecrireRegle(regles_t ** matRegles,char* regles,int nbRegle)
{
    FILE *file = fopen(regles, "w");
    if (file)
    {
        fprintf(file, "%d\n", nbRegle);

        for (int i = 0; i < nbRegle; i++)
        {
            fprintf(file,"%d %d %d %d %d %d %d %d %d %d\n",(matRegles[i]->droite),(matRegles[i]->haut),(matRegles[i]->gauche)
                                                    , (matRegles[i]->bas), (matRegles[i]->distance_fantome),(matRegles[i]->dir_pacman),
                                                    (matRegles[i]->dir_fantome), (matRegles[i]->dir_pacman), (matRegles[i]->action), (matRegles[i]->priorite));
        }
    }
    fclose(file);

}