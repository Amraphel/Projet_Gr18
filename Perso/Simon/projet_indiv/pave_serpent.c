#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

void draw(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    SDL_Rect rectangle;

    SDL_SetRenderDrawColor(renderer,
                           255, 255, 255, // mode Red, Green, Blue (tous dans 0..255)
                           255);          // 0 = transparent ; 255 = opaque
    rectangle.x = x;                      // x haut gauche du rectangle
    rectangle.y = y;                      // y haut gauche du rectangle
    rectangle.w = w;                      // sa largeur (w = width)
    rectangle.h = h;                      // sa hauteur (h = height)
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer,
                       x, y,  // x,y du point de la première extrémité
                       w+x, h+y); // x,y seconde extrémité
}
int getMaxSize(int *w, int *h)
{
    SDL_DisplayMode dm;

    if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
    {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        return 1;
    }
    *w = dm.w;
    *h = dm.h;

    return 0;
}
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    int w;
    int h;
    
    SDL_Window
        *window_1 = NULL;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }
    getMaxSize(&w, &h);
    /* Création de la fenêtre de gauche */
    window_1 = SDL_CreateWindow(
        "",    // codage en utf8, donc accents possibles
        0, 0,                  // coin haut gauche en haut gauche de l'écran
        w, h,              // largeur = 400, hauteur = 300
        SDL_WINDOW_RESIZABLE); // redimensionnable

    if (window_1 == NULL)
    {
        SDL_Log("Error : SDL window 1 creation - %s\n",
                SDL_GetError()); // échec de la création de la fenêtre
        SDL_Quit();              // On referme la SDL
        exit(EXIT_FAILURE);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window_1, -1, 0);
    draw(renderer, 10, h/4, 50, h/2);
    draw(renderer, w-60, h/4, 50, h/2);
    draw(renderer, w/2-10, h/2-10, 20, 20);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window_1);
    SDL_Quit(); // la SDL
    
    return 0;
}
