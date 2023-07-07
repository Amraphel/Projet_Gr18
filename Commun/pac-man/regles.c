#include "regles.h"

/**
 * @brief  initialise et créé un tableau de règles
 * @param [in] nbRegles
 * @return un tableau de règles
 */ 
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

/**
 * @brief charge des règles d'un fichier dans un tableau de règles
 * @param [in] regles fichier texte contenant les règles
 * @param [in] val0bj valeur objective
 * @return un tableau de règles
 */ 
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
         fclose(file);
    } else{
        exit(EXIT_FAILURE);
    }
    free(nbRegle);
   
    return matRegles;
}

/**
 * @brief écrit de nouvelles règles dans le fichier texte contenant les règles
 * @param [in] matRegles tableau de règles
 * @param [in] regles fichier texte contenant les regles
 * @param [in] nbRegle nombre de regles
 * @param [in] valObj valeur objective
 */ 
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
        fclose(file);
    }
    

}

/**
 * @brief initialise une règle
 * @param [in] nbRegle nombre de règles
 * @param [in] nbContrainte nombre de contrainte
 * @return une règle
 */ 
int * initRegle(int nbRegle, int nbContrainte){
    int * reg= malloc(sizeof(int)*nbRegle*nbContrainte);
    for(int i =0; i<nbRegle*nbContrainte; i++){
        reg[i]=i;
    }
    return reg;
}

/**
 * @brief échange aléatoirement des règles
 * @param [in] nbRegle nombre de règles
 * @param [in] nbContrainte nombre de contraintes 
 * @param [in] reg règle
 */ 
void shuffleRegle(int nbRegle, int nbContrainte, int * reg){
    for(int i=0; i <100; i++){
        int val1 = rand() %(nbRegle*nbContrainte);
        int val2 = rand() %(nbRegle*nbContrainte);
        int temp=reg[val1];
        reg[val1]=reg[val2];
        reg[val2]= temp;
    }
}