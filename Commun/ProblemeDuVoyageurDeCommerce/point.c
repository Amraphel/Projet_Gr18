#include "point.h"


/* Creation d'une liste de point avec des coordonnees aleatoire 
   nombreDePoint -> nombre de point maximun
   window -> fenetre dans laquelle le graphe sera affiché */
point_t* tabPointAleatoire(int nombreDePoint, SDL_Window *window)
{
    point_t* tabPoint=malloc(sizeof(point_t)*nombreDePoint);

    int i;
    for( i = 0; i < nombreDePoint; i++)
    {
        point_t point;
        
        int Wx ;
        int Wy;

        SDL_GetWindowSize(window, &Wx,&Wy);
        int x=  rand() % (Wx-50) + 1;
        int y= rand() % (Wy-50) + 1;

        point.x = x;
        point.y = y;

        tabPoint[i]=point;

        printf("%i %i\n", point.x, point.y);
    }

    return tabPoint;

}

