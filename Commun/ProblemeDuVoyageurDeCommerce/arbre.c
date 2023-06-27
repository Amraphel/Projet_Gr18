#include "arbre.h"


int **initMatrice(int nombreDePoint)
{
    int **matrice = malloc(sizeof(int *) * nombreDePoint);
    if (matrice)
    {
        int i;
        int j;
        for (i = 0; i < nombreDePoint; i++)
        {
            int *mat = malloc(sizeof(int) * nombreDePoint);
            matrice[i] = mat;

            for (j = 0; j < nombreDePoint; j++)
            {
                matrice[i][j] = 0;
                
            }
        }
    }
    return matrice;
}

void generer(int **matrice, int inf, int sup)
{

    if (inf < sup)
    {
        int k = (rand() % (sup - inf + 1)) + inf;
        matrice[inf][inf + 1] = 1;
        matrice[inf + 1][inf] = 1;
        if (k + 1 <= sup)
        {
            matrice[inf][k + 1] = 1;
            matrice[k + 1][inf] = 1;
        }
        generer(matrice, inf + 1, k);
        generer(matrice, k + 1, sup);
    }
}

// int main()
// {
//     int nb = 10;
//     int** matrice = initMatrice(nb);
//     generer(matrice, 0, nb -1);

//     for(int i = 0; i<nb; i++)
//     {
//         for(int j = 0; j <nb; j++)
//         {
//             printf("i = %i, j = %i, %i \n", i, j ,matrice[i][j]);
//         }
//     }
    
// }