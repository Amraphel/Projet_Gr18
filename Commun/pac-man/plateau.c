#include "plateau.h"

int ** create_plateau(int taille)
{
    int ** plateau=malloc(sizeof(int*)*taille);
    for (int i=0; i<taille; i++)
    {
        int * ligne=malloc(sizeof(int)*taille);
        for (int j=0; j<taille; j++)
        {
            plateau[i][j]=0;
        }
    }
    return plateau;
}

int ** init_murs(int ** plateau, int taille)
{
    int nb_images=10;
    int offset_x = source.w / nb_images;
    for (int i=0; i<taille; i++)
    {
        for(int j=0; j<taille; j++)
        {
            state.x=plateau[i][j]*offset_x;
        }
    }
}
