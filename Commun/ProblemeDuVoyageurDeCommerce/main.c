#include "affichage.h"
#include <time.h>

#define P 0.2

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
    SDL_Window *window = initWindow(200, 200, 600, 600);
    SDL_Renderer *renderer = initRenderer(window);
    point_t *tabPoint = NULL;
    tabPoint = tabPointAleatoire(NB, window);
    SDL_Rect *tabRect = createPoints(tabPoint, NB);

    int **mat = initMatrice(NB);
    generer(mat, 0, NB - 1);
    // genererGraphe(mat,P);
    cell_t *graphe = matToGraphe(mat, NB, tabPoint);
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
            }
        }
    }

    free(tabPoint);
    free(tabRect);

    end_sdl(1, "Normal ending", window, renderer);
}