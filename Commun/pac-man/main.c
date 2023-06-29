#include "affichage.h"
#include "fantome.h"
#include "plateau.h"

#define WINDOWL 700
#define WINDOWW 700

int main()
{
    int w;
    int h;
    int **plateau = loadPlateau("./source/lvl1.txt", &w, &h);
    printPlateau(plateau, w, h);
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_bool
        program_on = SDL_TRUE,
        event_utile = SDL_FALSE;

    SDL_Event
        event;

    SDL_Window *window = initWindow(200, 100, WINDOWW, WINDOWL);
    SDL_Renderer *renderer = initRenderer(window);
    SDL_Rect **tabRect = createTabRect(window, w, h);
    perso_t *Pac_man = initPac_man(plateau, w, h);
    perso_t *Blinky=initBlinky(plateau,w,h);
    afficherPlateau(tabRect, plateau, w, h, window, renderer);
    SDL_Rect rectPac = {Pac_man->posY * WINDOWL / h, Pac_man->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};
    SDL_Rect rectBlin = {Blinky->posY * WINDOWL / h, Blinky->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};
    afficherPerso(Blinky,window,renderer,&rectBlin);
    afficherPerso(Pac_man, window, renderer, &rectPac);
    // void movePersoInPlateau(plateau, perso.posX, perso.posY, w, h, 1);

    int speed = 100000;
    int speedMove = 200000;
    int i = 0;
    int move=0;
    int mort = 0;
    int etatAnimPac = 0;
    int etatAnimBlin =0;
    SDL_RenderPresent(renderer);
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
                case SDLK_DOWN:
                    if (mort != 1)
                    {
                        if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 1))
                        {
                            movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 1, &mort);
                            rectPac.y = rectPac.y + (WINDOWL / h);
                        }
                    }
                    break;
                case SDLK_UP:
                    if (mort != 1)
                    {
                        if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 3))
                        {
                            movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 3, &mort);
                            rectPac.y = rectPac.y - (WINDOWL / h);
                        }
                    }
                    break;
                case SDLK_RIGHT:
                    if (mort != 1)
                    {
                        if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 4))
                        {
                            movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 4, &mort);
                            rectPac.x = rectPac.x + (WINDOWW / w);
                        }
                    }
                    break;
                case SDLK_LEFT:
                    if (mort != 1)
                    {
                        if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 2))
                        {
                            movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 2, &mort);
                            rectPac.x = rectPac.x - (WINDOWW / w);
                        }
                    }
                default:
                    break;
                }
            }
        }
        if (mort != 1)
        {
            if (move == 0)
            {
                moveBlinky(window, plateau, w, h, Blinky, Pac_man, &rectBlin, &mort);
            }
            move = (move + 1) % speedMove;
            if (i == 0)
            {
                afficherPlateau(tabRect, plateau, w, h, window, renderer);
                animePerso(Pac_man, window, renderer, &rectPac, &etatAnimPac);
                animePerso(Blinky, window, renderer, &rectBlin, &etatAnimBlin);
                SDL_RenderPresent(renderer);
            }
            i = (i + 1) % speed;
        }
    }

    end_sdl(1, "Normal ending", window, renderer);

    return 0;
}