#include "affichage.h"
#include <time.h> 

#define P 0.2
#define NB 4

int main()
{
    time_t t;
    time(&t);
    srand(t);
    SDL_Window* window = initWindow(200,200,600,600);
    SDL_Renderer* renderer = initRenderer(window);
    point_t *tabPoint = NULL;
    tabPoint  = tabPointAleatoire(NB, window);
    SDL_Rect * tabRect= createPoints(tabPoint ,NB);


    int ** mat= initMatrice(NB);
    generer(mat,0,NB-1);
   // genererGraphe(mat,P);
    cell_t* graphe = matToGraphe(mat, NB, tabPoint);
    drawGraphe(renderer,tabRect,graphe,NB);
    SDL_Delay(6000);

    free(tabPoint);
    free(tabRect);


    end_sdl(1,"Normal ending", window, renderer);
}