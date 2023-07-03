#include "regleInky.h"

regles_t ** createMatRegles(int width, int height)
{
    regles_t **matRegles = malloc(sizeof(regles_t *) * width);
    for (int i = 0; i < width; i++)
    {
        int *ligne = malloc(sizeof(regles_t));
        matRegles[i] = ligne;
        for (int j = 0; j < height; j++)
        {
            matRegles[i][j] = 0;
        }
    }
    return matRegles;
}

regles_t **loadRegles(char *regles)
{
    regles_t **matRegles = NULL;
    FILE *file = fopen(regles, "r");
    int* w, h;
    if (file)
    {
        fscanf(file, "%d %d\n", w, h);

        matRegles = createMatRegles(*w, *h);
        for (int i = 0; i < *w; i++)
        {            
            fscanf(file, "%d %d %d %d %d %d %d %d %d %d \n", regles_t[i].droite, regles_t[i].gauche, regles_t[i].haut, regles_t[i].bas, regles_t[i].distance_fantome, regles_t[i].distance_pacman, regles_t[i].cadran_fantome, regles_t[i].cadran_pacman, regles_t[i].priorite, regles_t[i].action);

        }
    }
    fclose(file);
    return matRegles;
}

void loadRegles(regles_t ** matRegles, char * regles)
{
    FILE *file = fopen(regles, "w");
    int* w, h;
    if (file)
    {
        for (int i = 0; i < *w; i++)
        {            
            fprintf(file, "%d %d %d %d %d %d %d %d %d %d \n", matRegles[i].droite, matRegles[i].gauche, matRegles[i].haut, matRegles[i].bas, matRegles[i].distance_fantome, matRegles[i].distance_pacman, matRegles[i].cadran_fantome, matRegles[i].cadran_pacman, matRegles[i].priorite, matRegles[i].action);
        }
    }
    fclose(file);
}