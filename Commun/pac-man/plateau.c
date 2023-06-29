#include "plateau.h"

void coordPlat(int **plateau,int w, int h, int val, int *x, int *y)
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if(plateau[i][j] == val){
                *x=i;
                *y=j;
            }
        }
    }
}

int **create_plateau(int width, int height)
{
    int **plateau = malloc(sizeof(int *) * width);
    for (int i = 0; i < width; i++)
    {
        int *ligne = malloc(sizeof(int) * height);
        plateau[i] = ligne;
        for (int j = 0; j < height; j++)
        {
            plateau[i][j] = 0;
        }
    }
    return plateau;
}

void printPlateau(int **mat, int w, int h)
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            fprintf(stderr, "%d ", mat[i][j]);
        }
        fprintf(stderr, "\n");
    }
}

int **loadPlateau(char *lvl, int *w, int *h)
{
    int **plateau = NULL;
    FILE *file = fopen(lvl, "r");
    if (file)
    {
        fscanf(file, "%d %d\n", w, h);

        plateau = create_plateau(*w, *h);
        for (int i = 0; i < *w; i++)
        {
            for (int j = 0; j < *h; j++)
            {
                fscanf(file, "%d ", &plateau[i][j]);
            }
            fscanf(file, "\n");
        }
        // printPlateau(plateau, *w, *h);
    }
    fclose(file);
    return plateau;
}

void movePac_manInPlateau(int ** plateau, int* xPerso, int* yPerso, int direction)
{
    
    if( movePossible(plateau, xPerso, yPerso, direction) == 1)
    {
        //printf("%d\n")
        /*plateau[*xPerso][*yPerso] -= 100;
        plateau[xDeplacement][yDeplacement] = 99;
        *xPerso = xDeplacement;
        *yPerso = yDeplacement;*/
    }
}

//return 0 -> ne peux pas
//return 1 -> peux
int movePossible(int** plateau, int xPerso, int yPerso, int direction)
{
    int DeplacementPossible = 0;

    switch (direction)
    {
    case 1: // droite
        int xd = xPerso + 1;
        if(plateau[xd][yPerso] == 0 || plateau[xd][yPerso] == -1 || plateau[xd][yPerso] >= 200)
        {
            DeplacementPossible = 1;
        }
        break;

    case 2: // haut
        int yh = yPerso - 1;
        if(plateau[xPerso][yh] == 0 || plateau[xPerso][yh] == -1 || plateau[xPerso][yh] >= 200)
        {
            DeplacementPossible = 1;
        }
        break;

    case 3: // gauche
        int xg = xPerso - 1;
        if(plateau[xg][yPerso] == 0 || plateau[xg][yPerso] == -1 || plateau[xg][yPerso] >= 200)
        {
            DeplacementPossible = 1;
        }
        
    case 4: // bas
        int yb = yPerso + 1;
        if(plateau[xPerso][yb] == 0 || plateau[xPerso][yb] == -1 || plateau[xPerso][yb] >= 200)
        {
            DeplacementPossible = 1;
        }

    default:
        break;
    }
    return DeplacementPossible;
}

int gom_exist(int ** plateau, int taille)
{
    int rep=1;
    for (int i=0; i<taille; i++)
    {
        for (int j=0; j<taille; j++)
        {
            rep=rep*plateau[i][j];
        }
    }
    return rep;
}