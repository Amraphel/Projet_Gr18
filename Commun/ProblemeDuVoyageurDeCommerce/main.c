#include "affichage.h"
#include "parcours.h"
#include <time.h>

#define P 0.2
#define WINDOWL 700
#define WINDOWW 700

int main(int argc, char **argv)
{
    time_t t;
    time(&t);
    srand(42);
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

    SDL_Window* window = initWindow(200,100,WINDOWW,WINDOWL);
    SDL_Renderer* renderer = initRenderer(window);
    point_t *tabPoint = NULL;
    tabPoint = tabPointAleatoire(NB, window);
    SDL_Rect *tabRect = createPoints(tabPoint, NB);


    int ** mat= initMatrice(NB);
    generer(mat,0,NB-1);
    genererGraphe(mat,P,NB);
    cell_t* graphe = matToGraphe(mat, NB, tabPoint);
   // afficherMat(mat,NB);
    matToPoids(mat, NB,tabPoint);
   // afficherMat(mat,NB);

    int onycroit= fourmis(mat,NB, 2,0.1);
    fprintf(stderr, "poids final : %d\n", onycroit);
    drawGraphe(renderer, tabRect, graphe, NB);

    while (program_on)
    { 
        event_utile = SDL_FALSE;
        while (!event_utile && SDL_PollEvent(&event))
        {   
            switch (event.type)
            {                           
            case SDL_QUIT:              
                program_on = SDL_FALSE; 
                event_utile = SDL_TRUE;
                break;
            case SDL_KEYDOWN: 
                switch (event.key.keysym.sym)
                {                     
                case SDLK_ESCAPE:   
                case SDLK_q:       
                    program_on = 0; 
                    event_utile = SDL_TRUE;
                    break;
                default: 
                    break;
                }
                break;
            default: 
                break;
            }
        }
    }

    free(tabPoint);
    free(tabRect);

    end_sdl(1, "Normal ending", window, renderer);
}