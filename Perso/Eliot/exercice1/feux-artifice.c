#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

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

void destroyWin(SDL_Window **window_tab, int taille)
{
    int i;
    for (i = taille - 1; i > -1; i--)
    {
        if (window_tab[i])
        {
            SDL_DestroyWindow(window_tab[i]);
            window_tab[i] = NULL;
        }
    }
    free(window_tab);
    window_tab = NULL;
}

void destroyRen(SDL_Renderer **renderer_tab, int taille)
{
    int i;
    for (i = taille - 1; i > -1; i--)
    {
        if (renderer_tab[i])
        {
            SDL_DestroyRenderer(renderer_tab[i]);
            renderer_tab[i] = NULL;
        }
    }
    free(renderer_tab);
    renderer_tab = NULL;
}

void moveWin(SDL_Window **window_tab, int iter, int taille)
{
    int i;
    int x;
    int y;
    for (i = 0; i < taille; i++)
    {
        if (iter < 70)
        {
            SDL_GetWindowPosition(window_tab[i], &x, &y);
            SDL_SetWindowPosition(window_tab[i], x, y - 40);
        }
        else
        {
            SDL_GetWindowPosition(window_tab[i], &x, &y);
            switch (i)
            {
            case 0:
                x = x + 20;
                break;
            case 1:
                x = x + 20;
                y = y + 20;
                break;
            case 2:
                y = y + 20;
                break;
            case 3:
                x = x - 20;
                y = y + 20;
                break;
            case 4:
                x = x + 20;
                y = y - 20;
                break;
            case 5:
                x = x - 20;
                y = y - 20;
                break;
            case 6:
                y = y - 20;
                break;
            case 7:
                x = x - 10;
                break;
            default:
                break;
            }
            SDL_SetWindowPosition(window_tab[i], x, y);
        }
    }
    SDL_Delay(100);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    int w, h;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    SDL_Window **window_tab = malloc((sizeof(SDL_Window *) * 9));
    if (window_tab)
    {

        SDL_Renderer **renderer_tab = malloc(sizeof(SDL_Renderer *) * 9);
        if (renderer_tab)
        {

            getMaxSize(&w, &h);

            int i;
            for (i = 0; i < 8; i++)
            {
                SDL_Window *window = SDL_CreateWindow("", w / 2, (h - 200), 200, 200, SDL_WINDOW_RESIZABLE);
                if (window == NULL)
                {
                    SDL_Log("Error : SDL window 1 creation - %s\n",
                            SDL_GetError());
                    SDL_Quit();
                    exit(EXIT_FAILURE);
                }

                SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                SDL_SetRenderDrawColor(renderer, 255-i*40, 120+i*15, i*10, 255);
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);
                window_tab[i] = window;
                renderer_tab[i] = renderer;
            }

            i = 0;
            while (i < 100)
            {
                moveWin(window_tab, i, 8);
                i++;
            }
            destroyRen(renderer_tab, 8);
            destroyWin(window_tab, 8);
        }
    }

    SDL_Quit();

    return 0;
}