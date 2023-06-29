#include "affichage.h"
#include "fantome.h"
#include "plateau.h"


#define WINDOWL 700
#define WINDOWW 700

int main()
{
    int w;
    int h;
    int ** plateau=   loadPlateau("./source/lvl1.txt", &w, &h);
    printPlateau(plateau,w,h);
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window *window = initWindow(200, 100, WINDOWW, WINDOWL);
    SDL_Renderer *renderer = initRenderer(window);
    SDL_Rect** tabRect = createTabRect(window,w,h);
    afficherPlateau(tabRect,plateau,w,h,window,renderer);

    SDL_Delay(6000);
    end_sdl(1, "Normal ending", window, renderer);
    return 0;
}