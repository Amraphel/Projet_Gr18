#include "affichage.h"

void end_sdl(char ok,
             char const *msg,
             SDL_Window *window,
             SDL_Renderer *renderer)
{
    char msg_formated[255];
    int l;

    if (!ok)
    { // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
}

SDL_Window *initWindow(int x, int y, int w, int h)
{
    SDL_Window *window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError());
        exit(EXIT_FAILURE);
    }
    window = SDL_CreateWindow(
        "Fenêtre",
        x, y,
        w, h,
        SDL_WINDOW_RESIZABLE);

    if (window == NULL)
    {
        SDL_Log("Error : SDL window creation - %s\n",
                SDL_GetError()); // échec de la création de la fenêtre
        SDL_Quit();              // On referme la SDL
        exit(EXIT_FAILURE);
    }

    return window;
}

SDL_Renderer *initRenderer(SDL_Window *window)
{
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return renderer;
}

SDL_Rect* createPoints(point_t* listPoint, int nombreDePoint){
    SDL_Rect* tabPoint= malloc(sizeof(SDL_Rect)*nombreDePoint);
    int i=0;
    while(i<nombreDePoint){
        SDL_Rect point;
        point.x= listPoint[i].x;
        point.y=listPoint[i].y;
        point.w=20;
        point.h=20;
        tabPoint[i]=point;
        i++;
    }
    return tabPoint;
}

void drawPoints(SDL_Renderer* renderer, SDL_Rect* tabPoint,int nombreDePoint){
    for(int i=0; i<nombreDePoint; i++){
        SDL_RenderFillRect(renderer,&tabPoint[i] );

    }
}


void drawLine(SDL_Renderer* renderer, cell_t* graphe, int nbNoeud){
    int i;
    int j;
    for(i=0; i<nbNoeud; i++){
        for(j=0; j<nbNoeud; j++){
            if(graphe[i].lien[j]=1){
                SDL_RenderDrawLine(renderer, graphe[i].point.x+10, graphe[i].point.y+10,
                                                graphe[j].point.x+10, graphe[j].point.y+10);
            }
        }
    }
}

void drawGraphe(SDL_Renderer* renderer, SDL_Rect* tabPoint,cell_t* graphe,int nbNoeud){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    drawPoints(renderer,tabPoint,nbNoeud);
    drawLine(renderer,graphe,nbNoeud);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
}