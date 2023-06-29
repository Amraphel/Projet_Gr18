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
