#include "affichage.h"
#include <time.h>

#define P 1
#define WINDOWL 1000
#define WINDOWW 1000

int main(int argc, char **argv)
{
    SDL_bool
        program_on = SDL_TRUE,
        event_utile = SDL_FALSE;

    SDL_Event
        event;

    int NB;
    if (argc == 2)
    {
        sscanf(argv[1], "%d", &NB);
    }
    else
    {
        NB = 5;
    }
    time_t t;
    time(&t);
    srand(t);
    SDL_Window* window = initWindow(200,200,WINDOWW,WINDOWL);
    SDL_Renderer* renderer = initRenderer(window);
    point_t *tabPoint = NULL;
    tabPoint = tabPointAleatoire(NB, window);
    SDL_Rect *tabRect = createPoints(tabPoint, NB);


    int ** mat= initMatrice(NB);
    generer(mat,0,NB-1);
    genererGraphe(mat,P,NB);
    cell_t* graphe = matToGraphe(mat, NB, tabPoint);
    drawGraphe(renderer,tabRect,graphe,NB);
    SDL_Delay(3000);

    free(tabPoint);
    free(tabRect);

    end_sdl(1, "Normal ending", window, renderer);
}