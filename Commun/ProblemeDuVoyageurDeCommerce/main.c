#include "affichage.h"
#include "rechercheLocal.h"
#include <time.h>

#define P 0.2
#define WINDOWL 700
#define WINDOWW 700

int main(int argc, char **argv)
{
    time_t t;
    time(&t);
    srand(t);
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
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError());
        exit(EXIT_FAILURE);
    }
    

    SDL_Window* window = initWindow(200,100,WINDOWW,WINDOWL);
    SDL_Renderer* renderer = initRenderer(window);

    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

    point_t *tabPoint = NULL;
    tabPoint = tabPointAleatoire(NB, window);
    SDL_Rect *tabRect = createPoints(tabPoint, NB);

    int* tabType = NULL;
    tabType = initTypeNoeud(NB);


    int ** mat= initMatrice(NB);
    generer(mat,0,NB-1);
    genererGraphe(mat,P,NB);
    cell_t* graphe = matToGraphe(mat, NB, tabPoint);
    matToPoids(mat, NB,tabPoint);
    int numActuel = 0;
    int fini = 0;

   updateVisitable(tabType, graphe, NB, numActuel);

    int poidsFourmis= fourmis(mat,NB, 2,0.1);
    int poidsLocal= recherchelocal(mat,NB, 100 ,0.001);
    fprintf(stderr, "%d et %d\n", poidsFourmis, poidsLocal);
 

    int poidsParcours = 0;

    drawGraphe(renderer, tabRect, graphe, NB, tabType);

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
            case SDL_MOUSEBUTTONDOWN: // Click souris
                if (SDL_GetMouseState(NULL, NULL) &
                         SDL_BUTTON(SDL_BUTTON_LEFT))
                {                                   // Si c'est un click droit
                    int clickx = event.motion.x;
                    int clicky = event.motion.y;

                    if (fini == 0)
                    {
                        click(tabType, tabPoint, &numActuel, NB, clickx, clicky, &poidsParcours, mat);
                    }

                    updateVisitable(tabType, graphe, NB, numActuel);
                    drawGraphe(renderer, tabRect, graphe, NB, tabType);

                    fini = fin(tabType, numActuel, NB);
                    if (fini == 1)
                    {
                        int scoreAffiche = 0;
                        score(poidsParcours, poidsFourmis, poidsLocal, &scoreAffiche);
                        affichageScore(window, renderer, scoreAffiche);
                    }

                }
                event_utile = SDL_TRUE;
                break;
            default: 
                break;
            }
        }
    }

    free(tabPoint);
    free(tabRect);
    free(tabType);

    end_sdl(1, "Normal ending", window, renderer);
}