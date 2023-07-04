#include "plateau.h"

void coordPlat(int **plateau, int w, int h, int val, int *x, int *y)
{
    *x = 0;
    *y = 0;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (plateau[i][j] == val)
            {
                *x = i;
                *y = j;
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

// return 0 -> ne peux pas
// return 1 -> peux
int movePossible(int **plateau, int xPerso, int yPerso, int direction, int id, int* super)
{
    int DeplacementPossible = 0;
    int xd, yh, xg, yb;
    switch (direction)
    {
    case 1: // droite
        xd = xPerso + 1;
        if (plateau[xd][yPerso] == 0 || plateau[xd][yPerso] == -1 || plateau[xd][yPerso] >= 150 || plateau[xd][yPerso] == 99 || plateau[xd][yPerso] == 20)
        {
            DeplacementPossible = 1;
            if(plateau[xd][yPerso] == 20 && id == 99)
            {
                etatSuperPac(id, super);
            }
        }
        break;

    case 2: // haut
        yh = yPerso - 1;
        if (plateau[xPerso][yh] == 0 || plateau[xPerso][yh] == -1 || plateau[xPerso][yh] >= 150 || plateau[xPerso][yh] == 99 || plateau[xPerso][yh] == 20)
        {
            DeplacementPossible = 1;
            if(plateau[xPerso][yh] == 20 && id == 99)
            {
                etatSuperPac(id, super);
            }
        }
        break;

    case 3: // gauche
        xg = xPerso - 1;
        if (plateau[xg][yPerso] == 0 || plateau[xg][yPerso] == -1 || plateau[xg][yPerso] >= 150 || plateau[xg][yPerso] == 99 || plateau[xg][yPerso] == 20)
        {
            DeplacementPossible = 1;
            if(plateau[xg][yPerso] == 20 && id == 99)
            {
                etatSuperPac(id, super);
            }
        }
        break;
    case 4: // bas
        yb = yPerso + 1;
        if (plateau[xPerso][yb] == 0 || plateau[xPerso][yb] == -1 || plateau[xPerso][yb] >= 150 || plateau[xPerso][yb] == 99 || plateau[xPerso][yb] == 20)
        {
            DeplacementPossible = 1;
            if(plateau[xPerso][yb] == 20 && id == 99)
            {
                etatSuperPac(id, super);
            }
        }
        break;
    default:
        break;
    }
    return DeplacementPossible;
}

void movePersoInPlateau(int **plateau, int *xPerso, int *yPerso, int idPerso, int direction, int *mort, int* super)
{

    int xDeplacement = *xPerso;
    int yDeplacement = *yPerso;

    if (movePossible(plateau, *xPerso, *yPerso, direction, idPerso, super) == 1)
    {

        switch (direction)
        {
        case 1: // droite
            xDeplacement = *xPerso + 1;
            break;
        case 2: // haut
            yDeplacement = *yPerso - 1;
            break;
        case 3: // gauche
            xDeplacement = *xPerso - 1;
            break;
        case 4: // bas
            yDeplacement = *yPerso + 1;
            break;

        default:
            break;
        }
        if (idPerso == 99)
        {

            plateau[*xPerso][*yPerso] = -1;
            plateau[xDeplacement][yDeplacement] = 99;
        }
        else
        {
            if (plateau[xDeplacement][yDeplacement] == 99 && *super == 0)
            {
                *mort = 1;
            }
            plateau[*xPerso][*yPerso] -= idPerso;
            plateau[xDeplacement][yDeplacement] += idPerso;
        }
        *xPerso = xDeplacement;
        *yPerso = yDeplacement;
    }
}

int gom_exist(int **plateau, int w, int h)
{
    int rep = 1;
    int i = 0;
    int j = 0;

    while (i < w && rep != 0)
    {
        while (j < h && rep != 0)
        {
            rep = plateau[i][j];
            j++;
        }
        i++;
        j = 0;
    }

    return rep;
}

void savePlateau(int **plateau, int w, int h)
{
    FILE *file = fopen("./source/save.txt", "w");
    fprintf(file, "%d %d\n", w, h);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            fprintf(file, "%d ", plateau[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void freePlateau(int **plateau, int w)
{
    for (int i = 0; i < w; i++)
    {
        free(plateau[i]);
        plateau[i] = NULL;
    }
    free(plateau);
}

void etatSuperPac(int id, int* super)
{
    if(id == 99 && *super == 0)
    {
        *super = 1;
    }
}