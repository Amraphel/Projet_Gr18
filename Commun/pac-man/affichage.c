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

void afficherPlateau(SDL_Rect **tabRect, int **plateau, int w, int h, SDL_Window *window, SDL_Renderer *renderer, int *etatAnim)
{
    SDL_RenderClear(renderer);
    int fondW, fondH;
    SDL_Texture *my_texture = load_texture_from_image("./source/Murs.png", window, renderer);
    SDL_Texture *gom = load_texture_from_image("./source/Pac-gomme.png", window, renderer);
    SDL_Texture *supergom = load_texture_from_image("./source/SuperPacGomme.png", window, renderer);
    SDL_GetWindowSize(window, &fondW, &fondH);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (plateau[j][i] != -1 && plateau[j][i] < 99)
            {
                int nb_images = 0;
                if (plateau[j][i] != 0 && plateau[j][i] < 20)
                {
                    nb_images = 15;
                    SDL_Rect
                        source = {0},
                        state = {0};

                    SDL_QueryTexture(my_texture,
                                     NULL, NULL,
                                     &source.w, &source.h);

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
                else
                {
                    if (plateau[j][i] == 0)
                    {
                        nb_images = 1;
                        SDL_Rect
                            source = {0},
                            state = {0};

                        SDL_QueryTexture(gom,
                                         NULL, NULL,
                                         &source.w, &source.h);

                        int offset_x = source.w / nb_images,
                            offset_y = source.h;

                        state.x = 0;
                        state.y = 0;
                        state.w = offset_x;
                        state.h = offset_y;

                        SDL_RenderCopy(renderer, gom, // Préparation de l'affichage
                                       &state,
                                       &tabRect[i][j]);
                    }
                    else
                    {

                        nb_images = 4;
                        SDL_Rect source = {0}, state = {0};
                        SDL_QueryTexture(supergom, NULL, NULL, &source.w, &source.h);
                        state.x = (*etatAnim) * source.w / nb_images;
                        state.y = 0;
                        state.w = source.w / nb_images;
                        state.h = source.h;
                        // state = {(*etatAnim) * source.w / nb_images, source.h, source.w / nb_images, source.h};
                        SDL_RenderCopy(renderer, supergom, &state, &tabRect[i][j]);

                        
                    }
                }
            }
        }
    }
    *etatAnim += 1;
                        *etatAnim = (*etatAnim) % 4;
    SDL_DestroyTexture(my_texture);
}

void afficherPerso(SDL_Texture *my_texture, SDL_Renderer *renderer, SDL_Rect *RectPac)
{
    int nbw = 4;
    int nbh = 4;

    SDL_Rect pos = {0, 0, 0, 0};
    SDL_QueryTexture(my_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_Rect state = {0, 0, pos.w / nbw, pos.h / nbh};

    SDL_RenderCopy(renderer, my_texture, &state, RectPac);
}

void animePerso(SDL_Texture *my_texture, SDL_Renderer *renderer, SDL_Rect *rectPerso, int *etatAnim, int dir)
{
    int nbw = 4;
    int nbh = 4;

    SDL_Rect pos = {0, 0, 0, 0};
    SDL_QueryTexture(my_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_Rect state = {(*etatAnim) * pos.w / nbw, dir * pos.h / nbh, pos.w / nbw, pos.h / nbh};

    SDL_RenderCopy(renderer, my_texture, &state, rectPerso);

    *etatAnim += 1;
    *etatAnim = (*etatAnim) % nbw;
}

void afficherGameOver(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font)
{
    SDL_Color color = {219, 0, 0, 255};
    SDL_Surface *text_surface = NULL;

    text_surface = TTF_RenderText_Blended(font, "GAME OVER", color); // création du texte dans la surface
    if (text_surface == NULL)
    {
        end_sdl(0, "Can't create text surface", window, renderer);
    }

    int W, H;
    SDL_GetWindowSize(window, &W, &H);

    // Création de la texture du text
    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL)
    {
        end_sdl(0, "Can't create texture from surface", window, renderer);
    }

    SDL_FreeSurface(text_surface); // la surface ne sert plus à rien

    SDL_Rect pos = {W / 8, H / 2 - 62, 0, 0};                   // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);         // Ecriture du texte dans le renderer

    SDL_DestroyTexture(text_texture);
    // SDL_RenderPresent(renderer);
}

void afficherBravo(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font)
{
    SDL_Color color = {0, 219, 0, 255};
    SDL_Surface *text_surface = NULL;

    text_surface = TTF_RenderText_Blended(font, "BRAVO", color); // création du texte dans la surface
    if (text_surface == NULL)
    {
        end_sdl(0, "Can't create text surface", window, renderer);
    }

    int W, H;
    SDL_GetWindowSize(window, &W, &H);

    // Création de la texture du text
    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL)
    {
        end_sdl(0, "Can't create texture from surface", window, renderer);
    }

    SDL_FreeSurface(text_surface); // la surface ne sert plus à rien

    SDL_Rect pos = {W / 3.5, H / 2 - 62, 0, 0};                 // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);         // Ecriture du texte dans le renderer

    SDL_DestroyTexture(text_texture);
    // SDL_RenderPresent(renderer);
}

int collision(SDL_Rect rectPac, SDL_Rect **rectFan, int nbFan)
{
    int col = 0;
    int i = 1;

    int ptHautGauchePac = rectPac.x;
    int ptHautDroitPac = rectPac.x + rectPac.w;
    int ptBasGauchePac = rectPac.y + rectPac.h;
    int ptYPac = rectPac.y;

    int ptHautDroitFan, ptHautGaucheFan, ptBasGaucheFan;
    int ptYFan;

    while (i < nbFan + 1)
    {
        ptHautDroitFan = rectFan[i]->x + rectFan[i]->w;
        ptHautGaucheFan = rectFan[i]->x;
        ptBasGaucheFan = rectFan[i]->y + rectFan[i]->h;
        ptYFan = rectFan[i]->y;

        if (ptYFan == ptYPac)
        {
            if ((ptHautDroitFan <= ptHautDroitPac && ptHautDroitFan > ptHautGauchePac) ||
                (ptHautGaucheFan >= ptHautGauchePac && ptHautGaucheFan < ptHautDroitPac))
            {
                col = 1;
            }
        }
        else if (ptHautGaucheFan == ptHautGauchePac)
        {

            if ((ptYFan > ptYPac && ptYFan < ptBasGauchePac) ||
                (ptBasGaucheFan < ptBasGauchePac && ptBasGaucheFan > ptYPac))
            {

                col = 1;
            }
        }

        i++;
    }

    return col;
}

void animeFluide(SDL_Rect **rectPerso, int nbPerso, int *dir, int **plateau, perso_t **tabPerso)
{

    for (int k = 0; k < nbPerso; k++)
    {

        switch (dir[k])
        {
        case 1:
            rectPerso[k]->y += rectPerso[k]->h / 10;
            break;
        case 2:
            rectPerso[k]->x -= rectPerso[k]->w / 10;
            break;
        case 3:
            rectPerso[k]->y -= rectPerso[k]->h / 10;
            break;
        case 4:
            rectPerso[k]->x += rectPerso[k]->w / 10;
            break;
        default:
            break;
        }
    }
}