#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/
void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
{ // renderer à fermer
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
    {                                  // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL)
    {                              // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
        window = NULL;
    }

    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
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

void draw(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    SDL_Rect rectangle;

    SDL_SetRenderDrawColor(renderer, 50, 0, 50, 255);
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;

    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer,
                       0, 0,      // x,y du point de la première extrémité
                       400, 400); // x,y seconde extrémité
}

SDL_Rect createFish(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    

}

void moveFish(SDL_Renderer *renderer, SDL_Rect *tab, int taille, int dir, int w, int h)
{
    int i;
    SDL_SetRenderDrawColor(renderer, 0, 94, 184, 255);
    SDL_RenderClear(renderer);
    for (i = 0; i < taille; i++)
    {
        if (i == taille - 1)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        else if (i < (taille - 1) * 0.3 / 2 || (i < (taille - 1) * 0.6 && i > (taille - 1) * 0.3) || i > (taille - 1) * 0.8)
        {
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        switch (dir)
        {
        case 1:
            tab[i].x =(w+tab[i].x - 30)%w;
            break;
        case 2:
            tab[i].x = (tab[i].x + 30)%w;
            break;
        case 3:
            tab[i].y = (h+tab[i].y - 30)%h;
            break;
        case 4:
            tab[i].y = (tab[i].y + 30)%h;
            break;
        default:
            break;
        }
        SDL_RenderFillRect(renderer, &tab[i]);
    }
    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    int w;
    int h;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);
    getMaxSize(&w, &h);
    SDL_GetCurrentDisplayMode(0, &screen);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, w * 0.66,
                              h * 0.66,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    SDL_Rect fond;
    fond.x = 0;
    fond.y = 0;
    int fondW;
    int fondH;
    SDL_GetWindowSize(window, &fondW, &fondH);
    fond.w = fondW;
    fond.h = fondH;

    SDL_SetRenderDrawColor(renderer, 0, 94, 184, 255);
    SDL_RenderFillRect(renderer, &fond);


    SDL_Rect fish = createFish(renderer, 50, 50, 100, 50);
    SDL_RenderPresent(renderer);
    SDL_bool program_on = SDL_TRUE;
    SDL_bool event_utile;
    SDL_Event event;
    while (program_on)
    { // La boucle des évènements
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
                case SDLK_p:
                case SDLK_LEFT:

                    break;
                case SDLK_RIGHT:

                    break;
                case SDLK_UP:

                    break;
                case SDLK_DOWN:

                    break;
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
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}