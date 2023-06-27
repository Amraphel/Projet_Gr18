#include "affichage.h"
#include "arbre.h"


void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
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


SDL_Rect* drawPoints(SDL_Renderer* renderer, cell_t* listeNoeud, int nombreDePoint){
    SDL_Rect tabPoint[nombreDePoint];
    int i=0;
    while(i<nombreDePoint){
        SDL_Rect point;
        point.x= listeNoeud[i].point.x;
        point.y=listeNoeud[i].point.y;
        point.w=20;
        point.h=20;
        tabPoint[i]=point;
        i++;
    }

}