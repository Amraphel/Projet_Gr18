#include "point.h"


/* Creation d'une liste de point avec des coordonnees aleatoire 
   nombreDePoint -> nombre de point maximun
   window -> fenetre dans laquelle le graphe sera affiché */
point_t* tabPointAleatoire(int nombreDePoint, SDL_Window *window)
{
    int tailleGrille = 3*nombreDePoint;
    point_t* tabPoint=malloc(sizeof(point_t)*nombreDePoint);
    int** grille = malloc(sizeof(int*)*tailleGrille);
    int j;
    int k;
    for(j = 0; j < tailleGrille ; j++)
    {
        int *mat = malloc(sizeof(int) *tailleGrille);
        grille[j] = mat;
        for(k = 0; k < tailleGrille; k++)
        {
            grille[j][k] = 0;
        }
    }

    int i;
    for( i = 0; i < nombreDePoint; i++)
    {
        point_t point;
        
        int Wx ;
        int Wy;
        int EstPlace = 0; //0 non place, 1 place

        SDL_GetWindowSize(window, &Wx,&Wy);

        int WxCase = (Wx -50) / (tailleGrille);
        int WyCase = (Wy -50) / (tailleGrille);
        int infx, supx;
        int infy, supy;
        int x, y;
        
        while(EstPlace == 0)
        {
            x = rand() % (tailleGrille);
            y = rand() % (tailleGrille);

            if (grille[x][y] != 1)
            {
                int yh = y+1;
                int yb = y-1;
                if(yb < 0)
                {
                    yb = y;
                }
                if(yh > tailleGrille-1)
                {
                    yh = y;
                }
                int xd = x+1;
                int xg = x-1;
                if(xd > tailleGrille-1)
                {
                    xd = x;
                }
                if(xg < 0)
                {
                    xg = x;
                }


                grille[x][y] = 1;
                //horizontal
                grille[xd][y] = 1;
                grille[xg][y] = 1;
                //vertical
                grille[x][yh] = 1;
                grille[x][yb] = 1;
                //col gauche
                grille[xd][yb] = 1;
                grille[xg][yh] = 1;
                //col droite
                grille[xd][yb] = 1;
                grille[xg][yh] = 1;


                infx = x * WxCase;
                supx = infx + WxCase;
                int posx = rand() % (supx-infx -50) + infx;

                infy = y * WyCase;
                supy = infy + WyCase;
                int posy = rand() % (supy-infy -50) + infy;

                point.x = posx;
                point.y = posy;

                EstPlace = 1;
            }
        }

        tabPoint[i]=point;

        

    }

    for(j = 0; j < tailleGrille ; j++)
    {
        
        free(grille[j]);
    }
    free(grille);

    return tabPoint;

}


int* initTypeNoeud(int taille){
    int* tabType= malloc(sizeof(int)*taille);
    tabType[0]=4;
    for(int i =1; i<taille; i++){
        tabType[i]=0;
    }
    return tabType;
}


