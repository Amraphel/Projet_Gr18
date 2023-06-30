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
    perso_t *Blinky = initBlinky(plateau, w, h);
    perso_t *Clyde = initClyde(plateau, w, h);

    int super = 0;
    SDL_Texture *textPac = load_texture_from_image("./source/Pac-man.png", window, renderer);
    SDL_Texture *textBlin = load_texture_from_image("./source/Blinky.png", window, renderer);
    SDL_Texture *textCly = load_texture_from_image("./source/Clyde.png", window, renderer);
    SDL_Rect rectPac = {Pac_man->posY * WINDOWL / h, Pac_man->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};
    SDL_Rect rectBlin = {Blinky->posY * WINDOWL / h, Blinky->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};
    SDL_Rect rectCly = {Clyde->posY * WINDOWL / h, Clyde->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};
    if (Blinky->posX != 0)
    {
        afficherPerso(Blinky, window, textBlin, renderer, &rectBlin);
    }

    afficherPerso(Pac_man, window, textPac, renderer, &rectPac);
    if (Clyde->posX != 0)
    {
        afficherPerso(Clyde, window, textCly, renderer, &rectCly);
    }

    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

    TTF_Font *font = NULL;

    font = TTF_OpenFont("./Front/BadComic-Regular.ttf", 90);
    if (font == NULL)
    {
        end_sdl(0, "Can't load font", window, renderer);
    }

    int speed = 100000;
    int speedMove = 200000;
    int i = 0;
    int move = 0;
    int mort = 0;
    int etatAnim = 0;
    int keyPressed = 0;
    int direction = 0;
    Pac_man->etat = 0;
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
                    if (mort != 1 && gom_exist(plateau, w, h) == 0)
                    {
                        if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 1) && !keyPressed)
                        {
                            direction = 1;
                        }
                    }
                    break;
                case SDLK_UP:
                    if (mort != 1 && gom_exist(plateau, w, h) == 0)
                    {
                        if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 3) && !keyPressed)
                        {
                            direction = 3;
                        }
                    }
                    break;
                case SDLK_RIGHT:
                    if (mort != 1 && gom_exist(plateau, w, h) == 0)
                    {
                        if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 4) && !keyPressed)
                        {
                            direction = 4;
                        }
                    }
                    break;
                case SDLK_LEFT:
                    if (mort != 1 && gom_exist(plateau, w, h) == 0)
                    {
                        if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 2) && !keyPressed)
                        {
                            direction = 2;
                        }
                    }
                    break;
                case SDLK_SPACE:
                    if (super == 0)
                    {
                        textPac = load_texture_from_image("./source/SuperPac-man.png", window, renderer);
                        super = 1;
                    }
                    else
                    {
                        textPac = load_texture_from_image("./source/Pac-man.png", window, renderer);
                        super = 0;
                    }
                    break;
                default:
                    break;
                }
            }
        }
        if (mort != 1 && gom_exist(plateau, w, h) == 0)
        {
            if (move == 0)
            {
                if (movePossible(plateau, Pac_man->posX, Pac_man->posY, direction))
                {
                    switch (direction)
                    {
                    case 1:
                        movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 1, &mort);
                        rectPac.y = rectPac.y + (WINDOWL / h);
                        Pac_man->etat = 3;
                        break;
                    case 3:
                        movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 3, &mort);
                        rectPac.y = rectPac.y - (WINDOWL / h);
                        Pac_man->etat = 1;
                        break;
                    case 4:
                        movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 4, &mort);
                        rectPac.x = rectPac.x + (WINDOWW / w);
                        Pac_man->etat = 0;
                        break;
                    case 2:
                        movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, 2, &mort);
                        rectPac.x = rectPac.x - (WINDOWW / w);
                        Pac_man->etat = 2;
                        break;
                    default:
                        break;
                    }
                }
                if (Blinky->posX != 0)
                {
                    moveBlinky(window, plateau, w, h, Blinky, Pac_man, &rectBlin, &mort);
                }
                if (Clyde->posX != 0)
                {
                    moveClyde(window, plateau, w, h, Clyde, Pac_man, &rectCly, &mort);
                }
            }
            move = (move + 1) % speedMove;
            if (i == 0)
            {
                afficherPlateau(tabRect, plateau, w, h, window, renderer);
                animePerso(Pac_man, window, textPac, renderer, &rectPac, &etatAnim, Pac_man->etat);
                if (Blinky->posX != 0)
                {
                    animePerso(Blinky, window, textBlin, renderer, &rectBlin, &etatAnim, Blinky->etat);
                }

                if (Clyde->posX != 0)
                {
                    animePerso(Clyde, window, textCly, renderer, &rectCly, &etatAnim, Clyde->etat);
                }
                SDL_RenderPresent(renderer);
            }
            i = (i + 1) % speed;
        }
        if (mort == 1)
        {
            afficherGameOver(window, renderer, font);
        }
        if (gom_exist(plateau, w, h) != 0)
        {
            afficherBravo(window, renderer, font);
        }
    }

    end_sdl(1, "Normal ending", window, renderer);

    return 0;
}