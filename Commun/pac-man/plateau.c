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
        fscanf(file, "%d %d\n", h, w);

        plateau = create_plateau(*w, *h);
        for (int i = 0; i < *w; i++)
        {
            for (int j = 0; j < *h; j++)
            {
                fscanf(file, "%d ", &plateau[j][i]);
            }
            fscanf(file, "\n");
        }
        // printPlateau(plateau, *w, *h);
    }
    fclose(file);
    return plateau;
}

void movePersoInPlateau(int ** plateau, int* xPerso, int* yPerso, int wMaxPlateau, int hMaxPlateau, int direction)
{
    int xDeplacement, yDeplacement;
    int estDeplacer = 0;
    switch (direction)
    {
    case 1: // droite
        int xd = xPerso + 1;
        if (xd > wMaxPlateau - 1)
        {
            xDeplacement = xPerso;
        }
        else
        {
            xDeplacement = xd;
            estDeplacer = 1;
        }
        break;

    case 2: // haut
        int yh = yPerso - 1;
        if (yh > hMaxPlateau - 1)
        {
            yDeplacement = yPerso;
        }
        else
        {
            yDeplacement = yh;
            estDeplacer = 1;
        }
        break;

    case 3: // gauche
        int xg = xPerso - 1;
        if (xg < 0)
        {
            xDeplacement = xPerso;
        }
        else
        {
            xDeplacement = xg;
            estDeplacer = 1;
        }
        break;

    case 4: // bas
        int yb = yPerso + 1;
        if (yb < 0)
        {
            yDeplacement = yPerso;
        }
        else
        {
            yDeplacement = yb;
            estDeplacer = 1;
        }
        break;

    default:
        break;
    }
    if( estDeplacer == 1)
    {
        //plateau[xPerso][yPerso] -= 100;
        //plateau[xDeplacement][yDeplacement] = 99;
        //*xPerso = xDeplacement;
        //*yPerso = yDeplacement;
    }
}