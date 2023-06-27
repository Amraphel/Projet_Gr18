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
        int x=  rand() % Wx + 1;
        int y= rand() % Wy + 1;

        point.x = x;
        point.y = y;

        tabPoint[i]=point;

        printf("%i %i\n", point.x, point.y);
    }

    return tabPoint;

}

int main()
{
    int nb = 3;
    SDL_Window *window = NULL;
    

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }
     window = SDL_CreateWindow(
      "Fenêtre 1",           // codage en utf8, donc accents possibles
      0, 0,                  // coin haut gauche en haut gauche de l'écran
      100, 100,               // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE); // redimensionnable

  if (window == NULL)
  {
    SDL_Log("Error : SDL window 1 creation - %s\n",
            SDL_GetError()); // échec de la création de la fenêtre
    SDL_Quit();              // On referme la SDL
    exit(EXIT_FAILURE);
  }

  point_t* p =NULL;
  p =tabPointAleatoire(nb, window);
    free(p);
}
