#include "touche.h"

int deplacement(int move, perso_t *Pac_man, int **plateau, SDL_Rect **tabRectPerso, perso_t **tabPerso, int nbFan, SDL_Rect rectPac, int w, int h, int pause, int keyPressed)
{
    int direction;
    int dir;
    switch (move)
    {
    case 4:
        dir = 4;
        break;
    case 3:
        dir = 3;
        break;
    case 2:
        dir = 2;
        break;
    case 1:
        dir = 1;
        break;

    default:
        break;
    }

    if (collision(rectPac, tabRectPerso, nbFan, tabPerso) != 1 && gom_exist(plateau, w, h) == 0 && pause != 1)
    {
        if (movePossible(plateau, Pac_man->posX, Pac_man->posY, dir, Pac_man->id, &Pac_man->super) && !keyPressed)
        {
            direction = dir;
        }
    }

    return direction;
}

void destroyAllSDL(SDL_Texture *textBlin, SDL_Texture *textBlinNormal, SDL_Texture *textPac, SDL_Texture *textPacNormal, SDL_Texture *textPacSuper, SDL_Texture *textCly, SDL_Texture *textClyNormal,
                   SDL_Texture *textInk, SDL_Texture *textInkNormal, SDL_Texture *textPin, SDL_Texture *textPinNormal, SDL_Texture *textFanSuper, SDL_Renderer *renderer, SDL_Window *window)
{
    SDL_DestroyTexture(textBlin);
    SDL_DestroyTexture(textBlinNormal);

    SDL_DestroyTexture(textPac);
    SDL_DestroyTexture(textPacNormal);
    SDL_DestroyTexture(textPacSuper);


    SDL_DestroyTexture(textCly);
    SDL_DestroyTexture(textClyNormal);

    SDL_DestroyTexture(textInk);
    SDL_DestroyTexture(textInkNormal);

    SDL_DestroyTexture(textPin);
    SDL_DestroyTexture(textPinNormal);

    SDL_DestroyTexture(textFanSuper);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void finDeJeu(SDL_Rect rectPac, SDL_Rect **tabRectPerso, int nbFan, perso_t **tabPerso, int WINDOWW, int WINDOWL, TTF_Font* font, int**plateau, SDL_Window* window, SDL_Renderer*  renderer, int w, int h)
{
    if (collision(rectPac, tabRectPerso, nbFan, tabPerso) == 1 && tabPerso[0]->super == 0)
    {
        SDL_Color couleurGameOver = {219, 0, 0, 255};
        afficherTexteFin(window, renderer, font, couleurGameOver, "Game Over", WINDOWW / 8, WINDOWL / 2 - 62);
    }
    if (gom_exist(plateau, w, h) != 0)
    {
        SDL_Color couleurBravo = {0, 219, 0, 255};
        afficherTexteFin(window, renderer, font, couleurBravo, "Bravo", WINDOWW / 3.5, WINDOWL / 2 - 62);
    }
}