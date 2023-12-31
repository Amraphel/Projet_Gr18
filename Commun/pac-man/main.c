#include "affichage.h"
#include "fantome.h"
#include "touche.h"
#ifndef PLATEAU
#define PLATEAU
#include "plateau.h"
#endif
#ifndef REGLE
#define REGLE
#include "calculRegle.h"
#endif


// #define WINDOWL 700
// #define WINDOWW 700
#define NBREGLE 20
#define S 4

int main()
{
    int w;
    int h;
    time_t t;
    time(&t);
    int valObj=0;
    srand(t);
    int **plateau = loadPlateau("./source/lvl/lvl3.txt", &w, &h);
    // printPlateau(plateau,w,h);
    regles_t** regle =loadRegles("./source/regles/regle4.txt",&valObj);
    int WINDOWW = w * (700 / w);
    int WINDOWL = h * (700 / h);
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
    perso_t *Blinky = initFantome(plateau, w, h, 200);
    perso_t *Clyde = initFantome(plateau, w, h, 210);
    perso_t *Inky = initFantome(plateau, w, h, 220);
    perso_t *Pinky = initFantome(plateau, w, h, 230);
    perso_t **tabPerso = malloc(sizeof(perso_t *) * 5);
    if(tabPerso == NULL)
    {
        printf("Erreur de malloc tabPerso\n");
        exit(EXIT_FAILURE);
    }
    tabPerso[0] = Pac_man;
    tabPerso[1] = Blinky;
    tabPerso[2] = Clyde;
    tabPerso[3] = Inky;
    tabPerso[4] = Pinky;

    int *dir = malloc(sizeof(int) * 5);
    if(dir == NULL)
    {
        printf("Erreur de malloc dir\n");
        exit(EXIT_FAILURE);
    }
    dir[0] = 0;
    dir[1] = 0;
    dir[2] = 0;
    dir[3] = 0;
    dir[4] = 0;

    SDL_Texture *textPacNormal = load_texture_from_image("./source/Pac-man.png", window, renderer);
    SDL_Texture *textPacSuper = load_texture_from_image("./source/SuperPac-man.png", window, renderer);
    SDL_Texture *textPac = NULL;

    SDL_Texture *textBlinNormal = load_texture_from_image("./source/Blinky.png", window, renderer);
    SDL_Texture *textBlin = NULL;

    SDL_Texture *textClyNormal = load_texture_from_image("./source/Clyde.png", window, renderer);
    SDL_Texture *textCly = NULL;

    SDL_Texture *textInkNormal = load_texture_from_image("./source/Inky.png", window, renderer);
    SDL_Texture *textInk = NULL;

    SDL_Texture *textPinNormal = load_texture_from_image("./source/Pinky.png", window, renderer);
    SDL_Texture *textPin = NULL;

    SDL_Texture *textFanSuper = load_texture_from_image("./source/fantomeChasse.png", window, renderer);

    SDL_Rect rectPac = {Pac_man->posY * WINDOWL / h, Pac_man->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};
    SDL_Rect rectBlin = {Blinky->posY * WINDOWL / h, Blinky->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};
    SDL_Rect rectCly = {Clyde->posY * WINDOWL / h, Clyde->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};
    SDL_Rect rectInk = {Inky->posY * WINDOWL / h, Inky->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};
    SDL_Rect rectPin = {Pinky->posY * WINDOWL / h, Pinky->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};

    int nbFan = 4;
    SDL_Rect **tabRectPerso = malloc(sizeof(SDL_Rect *) * 5);
    if(tabRectPerso == NULL)
    {
        printf("Erreur de malloc tabRectPerso\n");
        exit(EXIT_FAILURE);
    }
    tabRectPerso[0] = &rectPac;
    tabRectPerso[1] = &rectBlin;
    tabRectPerso[2] = &rectCly;
    tabRectPerso[3] = &rectInk;
    tabRectPerso[4] = &rectPin;

    int* tempsMortFantome;
    tempsMortFantome = initTabTempsMortFantome(nbFan);

    if (TTF_Init() < 0)
        end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

    TTF_Font *font = NULL;

    font = TTF_OpenFont("./Front/videotype.ttf", 90);
    if (font == NULL)
    {
        end_sdl(0, "Can't load font", window, renderer);
    }


    int speedMove = 500;
    int speed = speedMove / 10;
    int speedDep = speedMove / 10;
    int i = 0;
    int move = 0;
    int animeF = 0;
    int mort = 0;
    int etatAnim = 0;
    int etatAnimPlat = 0;
    int keyPressed = 0;
    Pac_man->etat = 0;
    int timer = 0;
    int compt = 0;
    int oldDir = 0;
    int direction=0;
    int pause = 0;
    
    afficherPerso(textPacNormal, renderer, &rectPac);
    animeFantome(tabPerso, 1, textBlin, textBlinNormal, textFanSuper, &etatAnim, renderer,tempsMortFantome, &rectBlin);
    animeFantome(tabPerso, 2, textCly, textClyNormal, textFanSuper, &etatAnim, renderer,tempsMortFantome, &rectCly);
    animeFantome(tabPerso, 3, textInk, textInkNormal, textFanSuper, &etatAnim, renderer,tempsMortFantome, &rectInk);
    animeFantome(tabPerso, 4, textPin, textPinNormal, textFanSuper, &etatAnim, renderer,tempsMortFantome, &rectPin);

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
                    direction = deplacement(1, Pac_man, plateau, tabRectPerso, tabPerso, nbFan, rectPac, w, h, pause, keyPressed);
                    break;
                case SDLK_UP:
                    direction = deplacement(3, Pac_man, plateau, tabRectPerso, tabPerso, nbFan, rectPac, w, h, pause, keyPressed);
                    break;
                case SDLK_RIGHT:
                    direction = deplacement(4, Pac_man, plateau, tabRectPerso, tabPerso, nbFan, rectPac, w, h, pause, keyPressed);
                    break;
                case SDLK_LEFT:
                    direction = deplacement(2, Pac_man, plateau, tabRectPerso, tabPerso, nbFan, rectPac, w, h, pause, keyPressed);
                    break;
                case SDLK_p:
                    pause = enPause(pause);
                    break;
                case SDLK_s:
                    savePlateau(plateau, w, h);
                    break;
                default:
                    break;
                }
            }
        }
        int temp;
        if (collision(rectPac, tabRectPerso, nbFan, tabPerso) != 1 && gom_exist(plateau, w, h) == 0 && pause != 1)
        {
            if (move == 0)
            {

                dir[0] = movePacmanIA(plateau, Pac_man);
                
                //dir[0]=direction;
                if (Blinky->posX != 0)
                {
                    //dir[1] = moveBlinky(window, plateau, w, h, Blinky, Pac_man);
                    dir[1]= movePersoRegle(regle, plateau,tabPerso,1,NBREGLE,S,w);
                }
                if (Clyde->posX != 0)
                {
                    // dir[2] = moveClyde(window, plateau, w, h, Clyde, Pac_man);
                    dir[2]= movePersoRegle(regle, plateau,tabPerso,2,NBREGLE,S,w);
                }
                if (Inky->posX != 0)
                {
                    // dir[3] = moveClyde(window, plateau, w, h, Inky, Pac_man);
                    dir[3]= movePersoRegle(regle, plateau,tabPerso,3,NBREGLE,S,w);
                }
                if (Pinky->posX != 0)
                {
                    // dir[4] = moveClyde(window, plateau, w, h, Pinky, Pac_man);
                    dir[4]= movePersoRegle(regle, plateau,tabPerso,4,NBREGLE,S,w);
                }
                for (int j = 0; j < 5; j++)
                {
                    movePersoInPlateau(plateau, &tabPerso[j]->posX, &tabPerso[j]->posY, tabPerso[j]->id, dir[j], &mort, &tabPerso[j]->super);
                }

                if (Pac_man->super == 1)
                {
                    oldDir = dir[0];
                    compt = 0;
                    dir[0] = movePacmanIA(plateau, Pac_man);
                    movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, Pac_man->id, dir[0], &mort, &Pac_man->super);
                    
                    temp = dir[0];
                }

                if (Pac_man->super == 1)
                {
                    dir[0] = oldDir;
                    switchDirection(dir[0], Pac_man);
                    oldDir = temp;
                }
                direction = 0;
            }
            if (compt == 5 && Pac_man->super == 1)
            {
                dir[0] = oldDir;
                switchDirection(dir[0], Pac_man);
            }
            move = (move + 1) % speedMove;
            if (animeF == 0)
            {

                afficherPlateau(tabRect, plateau, w, h, window, renderer, &etatAnimPlat);
                animeFluide(tabRectPerso, 5, dir, WINDOWW, WINDOWL);
                if (Pac_man->super == 1)
                {
                    compt++;
                    if (Pac_man->super == 1)
                    {
                        timer += 1;
                    }
                    animeFluide(tabRectPerso, 1, dir, WINDOWW, WINDOWL);
                    if (timer >= 100)
                    {

                        Pac_man->super = 0;
                        timer = 0;
                    }
                }
            }
            animeF = (animeF + 1) % speedDep;

            if (i == 0)
            {
                afficherPlateau(tabRect, plateau, w, h, window, renderer, &etatAnimPlat);
                animePacMan(Pac_man, textPac, textPacNormal, textPacSuper,&etatAnim, renderer, &rectPac);
                animeFantome(tabPerso, 1, textBlin, textBlinNormal, textFanSuper, &etatAnim, renderer,tempsMortFantome, &rectBlin);
                animeFantome(tabPerso, 2, textCly, textClyNormal, textFanSuper, &etatAnim, renderer,tempsMortFantome, &rectCly);
                animeFantome(tabPerso, 3, textInk, textInkNormal, textFanSuper, &etatAnim, renderer,tempsMortFantome, &rectInk);
                animeFantome(tabPerso, 4, textPin, textPinNormal, textFanSuper, &etatAnim, renderer,tempsMortFantome, &rectPin);
                reapparitionFantome(tempsMortFantome, tabPerso, nbFan, tabRectPerso, dir, plateau);
                finDeJeu(rectPac, tabRectPerso, nbFan, tabPerso, WINDOWW, WINDOWL, font, plateau, window, renderer, w, h);

                SDL_RenderPresent(renderer);
            }
            i = (i + 1) % speed;
        }
    }

    freePlateau(plateau, w);

    free(tabRectPerso);
    free(tempsMortFantome);

    destroyAllSDL(textBlin, textBlinNormal, textPac, textPacNormal, textPacSuper, textCly, textClyNormal, textInk, textInkNormal, textPin, textPinNormal, textFanSuper, renderer, window);
    end_sdl(1, "Normal ending", window, renderer);
    for (int i = 0; i < 5; i++)
    {
        free(tabPerso[i]);
        free(tabRect[i]);
    }
    free(tabPerso);
    free(tabRect);
    free(dir);
    freeCerveau(regle, NBREGLE);

    return 0;
}