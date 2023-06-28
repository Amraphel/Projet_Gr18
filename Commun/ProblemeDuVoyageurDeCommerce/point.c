#include "point.h"


/* Creation d'une liste de point avec des coordonnees aleatoire 
   nombreDePoint -> nombre de point maximun
   window -> fenetre dans laquelle le graphe sera affiché */
point_t* tabPointAleatoire(int nombreDePoint, SDL_Window *window)
{
    point_t* tabPoint=malloc(sizeof(point_t)*nombreDePoint);
    int** grille = malloc(sizeof(int*)*3*nombreDePoint);
    int j;
    int k;
    for(j = 0; j < 3*nombreDePoint ; j++)
    {
        int *mat = malloc(sizeof(int) *3*nombreDePoint);
        grille[j] = mat;
        for(k = 0; k < 3*nombreDePoint; k++)
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

        int WxCase = Wx / (3 * nombreDePoint);
        int WyCase = Wy / (3 * nombreDePoint);
        int infx, supx;
        int infy, supy;
        int x, y;
        int tailleGrille = 3*nombreDePoint-1;

        //int x= rand() % (Wx-50) + 1;
        //int y= rand() % (Wy-50) + 1;
        while(EstPlace == 0)
        {
            x = rand() % ((3 * nombreDePoint)-1) + 1;
            y = rand() % ((3 * nombreDePoint)-1) + 1;

            if (grille[x][y] != 1)
            {
                int yh = y+1;
                int yb = y-1;
                if(yh < 0)
                {
                    yh = y;
                }
                if(yb > tailleGrille)
                {
                    yb = y;
                }
                int xd = x+1;
                int xg = x-1;
                if(xd > tailleGrille)
                {
                    xd = x;
                }
                if(xg < 0)
                {
                    xg = x;
                }

                printf("B %i %i\n", x, y);


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
                x = rand() % (supx-infx -50) + infx;

                infy = y * WyCase;
                supy = infy + WyCase;
                y = rand() % (supy-infy -50) + infy;

                EstPlace = 1;
            }
        }

        point.x = x;
        point.y = y;

        tabPoint[i]=point;

    }

    return tabPoint;

}

