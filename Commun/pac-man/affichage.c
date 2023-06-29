#include "affichage.h"

SDL_Rect **createTabRect(SDL_Window *window, int w, int h)
{
    SDL_Rect **tabRect = malloc(sizeof(SDL_Rect *) * w);
    int fondW, fondH;
    SDL_GetWindowSize(window, &fondW, &fondH);
    int larg = fondW / w;
    int haut = fondH / h;
    for (int i = 0; i < w; i++)
    {

        SDL_Rect *ligneRect = malloc(sizeof(SDL_Rect) * w);
        tabRect[i] = ligneRect;
        for (int j = 0; j < h; j++)
        {
            SDL_Rect rect;
            rect.x = i * larg;
            rect.y = j * haut;
            rect.w = larg;
            rect.h = haut;
            tabRect[i][j] = rect;
        }
    }
    return tabRect;
}

void afficherPlateau(SDL_Rect **tabRect, int **plateau, int w, int h, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    int fondW, fondH;
    SDL_Texture *my_texture = load_texture_from_image("./source/Murs.png", window, renderer);
    SDL_GetWindowSize(window, &fondW, &fondH);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (plateau[j][i] != 0 && plateau[j][i] != 99)
            {
                SDL_Rect
                    source = {0},
                    state = {0};

                SDL_QueryTexture(my_texture,
                                 NULL, NULL,
                                 &source.w, &source.h);

                int nb_images = 15;
                int offset_x = source.w / nb_images,
                    offset_y = source.h;

                state.x = (plateau[j][i] - 1) * offset_x;
                state.y = 0;
                state.w = offset_x;
                state.h = offset_y;

                SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                               &state,
                               &tabRect[i][j]);
            }
        }
    }
}

void afficherPerso(perso_t *perso, SDL_Window *window, SDL_Renderer *renderer, SDL_Rect *RectPac)
{
    char pathImg[255];
    int nbw = 0;
    int nbh = 0;
    switch (perso->id)
    {
    case 99:
        sprintf(pathImg, "./source/Pac-man.png");
        nbw = 4;
        nbh = 4;
        break;
    case 200:
        sprintf(pathImg, "./source/Blinky.png");
        nbw = 3;
        nbh = 1;
        break;

    default:
        break;
    }
    SDL_Texture *my_texture = load_texture_from_image(pathImg, window, renderer);
    SDL_Rect pos = {0, 0, 0, 0};
    SDL_QueryTexture(my_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_Rect state = {0, 0, pos.w / nbw, pos.h / nbh};

    SDL_RenderCopy(renderer, my_texture, &state, RectPac);
}

void animePerso(perso_t *perso, SDL_Window *window, SDL_Renderer *renderer, SDL_Rect *rectPerso, int *etatAnim, int direction)
{
    char pathImg[255];
    int nbw = 0;
    int nbh = 0;
    switch (perso->id)
    {
    case 99:
        sprintf(pathImg, "./source/Pac-man.png");
        nbw = 4;
        nbh = 4;

        break;
    case 200:
        sprintf(pathImg, "./source/Blinky.png");
        nbw = 3;
        nbh = 1;

        break;

    default:
        break;
    }
    SDL_Texture *my_texture = load_texture_from_image(pathImg, window, renderer);
    SDL_Rect pos = {0, 0, 0, 0};
    SDL_QueryTexture(my_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_Rect state = {(*etatAnim) * pos.w / nbw, direction*pos.h/nbh, pos.w / nbw, pos.h / nbh};

    SDL_RenderCopy(renderer, my_texture, &state, rectPerso);

    *etatAnim += 1;
    *etatAnim = (*etatAnim) % nbw;
}
