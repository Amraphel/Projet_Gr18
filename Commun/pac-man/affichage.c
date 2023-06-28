#include "affichage.h"

void end_sdl(char ok,
             char const *msg,
             SDL_Window *window,
             SDL_Renderer *renderer)
{
    char msg_formated[255];
    int l;

    if (!ok)
    { 
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

    
    window = SDL_CreateWindow(
        "Fenêtre",
        x, y,
        w, h,
        SDL_WINDOW_RESIZABLE);

    if (window == NULL)
    {
        SDL_Log("Error : SDL window creation - %s\n",
                SDL_GetError()); 
        SDL_Quit();              
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