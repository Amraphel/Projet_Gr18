#include "affichage.h"


/**
 * @brief Creation d'un tableau de SDL_Rect. fenetre découper en grille de SDL_Rect
 * @param [in] window fenetre de jeu 
 * @param [in] w largeur du plateau de jeu  
 * @param [in] h longueur du plateau de jeu
 * @return un tableau de SDL_Rect
 */
SDL_Rect **createTabRect(SDL_Window *window, int w, int h)
{
    SDL_Rect **tabRect = malloc(sizeof(SDL_Rect *) * w);
    if(tabRect == NULL)
    {
        printf("Erreur de malloc tabrect\n");
        exit(EXIT_FAILURE);
    }
    int fondW, fondH;
    SDL_GetWindowSize(window, &fondW, &fondH);
    int larg = fondW / w;
    int haut = fondH / h;
    for (int i = 0; i < w; i++)
    {

        SDL_Rect *ligneRect = malloc(sizeof(SDL_Rect) * w);
        if (ligneRect == NULL)
        {
            printf("Erreur de malloc ligneRect\n");
            exit(EXIT_FAILURE);
        }
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

/**
 * @brief Affiche le plateau de jeu avec les gom, les murs, super gom
 * @param [in] tabRect tableau de SDL_Rect 
 * @param [in] plateau matrice du plateau de jeu
 * @param [in] W largeur du plateau de jeu
 * @param [in] h largeur longueur du plateau de jeu
 * @param [in] window fenetre de jeu
 * @param [in] renderer renderer de la fenetre de jeu
 * @param [in] etatAnim etat de l'animation en cours
 */
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
                if (plateau[j][i] != 0 && plateau[j][i] < 20)
                {
                    chargerTextureMap(my_texture, plateau, 15, tabRect, renderer, i, j, 0, etatAnim);
                }
                else
                {
                    if (plateau[j][i] == 0)
                    {
                        chargerTextureMap(gom, plateau, 1, tabRect, renderer, i, j, 1, etatAnim);
                    }
                    else
                    {
                        chargerTextureMap(supergom, plateau, 4, tabRect, renderer, i, j, 2, etatAnim);
                    }
                }
            }
        }
    }
    *etatAnim += 1;
                        *etatAnim = (*etatAnim) % 4;
    SDL_DestroyTexture(my_texture);
    SDL_DestroyTexture(gom);
    SDL_DestroyTexture(supergom);
}

/**
 * @brief charge une texture dans le renderer de la fenêtre de jeu
 * @param [in] texture texture à charger
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] nb_images nombre d'images dont est composée une ligne de la texture
 * @param [in] tabRect rectangle dans lequel on charge la texture
 * @param [in] renderer renderer de la fenêtre de jeu
 * @param [in] i ligne du plateau où on veut charger la texture
 * @param [in] j colonne du plateau où on veut charger la texture
 * @param [in] type type de texture à afficher (mur, pac-gomme, personnage)
 * @param [in] etatAnim état de l'animation d'un personnage
 */ 
void chargerTextureMap(SDL_Texture *texture,int **plateau, int nb_images, SDL_Rect **tabRect, SDL_Renderer* renderer, int i, int j, int type, int *etatAnim)
{
    SDL_Rect
        source = {0},
        state = {0};

    SDL_QueryTexture(texture,
                     NULL, NULL,
                     &source.w, &source.h);

    int offset_x = source.w / nb_images,
        offset_y = source.h;

    switch (type)
    {
    case 0:
        state.x = (plateau[j][i] - 1) * offset_x;
        state.y = 0;
        state.w = offset_x;
        state.h = offset_y;
        break;
    case 1:
        state.x = 0;
        state.y = 0;
        state.w = offset_x;
        state.h = offset_y;
        break;
    case 2:
        state.x = (*etatAnim) * source.w / nb_images;
        state.y = 0;
        state.w = source.w / nb_images;
        state.h = source.h;
        break;
    
    default:
        break;
    }

    

    SDL_RenderCopy(renderer, texture, // Préparation de l'affichage
                   &state,
                   &tabRect[i][j]);
}

/**
 * @brief Affiche un personnage sur le plateau
 * @param [in] texture_perso texture du perso
 * @param [in] renderer renderer de la fenetre
 * @param [in] rectPerso rectangle du perso
 */
void afficherPerso(SDL_Texture *texture_perso, SDL_Renderer *renderer, SDL_Rect *rectPerso)
{
    int nbw = 4; //nombre de sprite sur une ligne
    int nbh = 4; //nombre de sprite sur une colonne

    SDL_Rect pos = {0, 0, 0, 0};
    SDL_QueryTexture(texture_perso, NULL, NULL, &pos.w, &pos.h); 
    SDL_Rect state = {0, 0, pos.w / nbw, pos.h / nbh};

    SDL_RenderCopy(renderer, texture_perso, &state, rectPerso);
}

/**
 * @brief Anime le personnage sur le plateau lors du deplacement
 * @param [in] texture_perso texture du perso
 * @param [in] renderer renderer de la fenetre
 * @param [in] rectPerso rectangle du perso
 * @param [in] etatAnim etat de l'animation du perso
 * @param [in] direction direction du perso
 */
void animePerso(SDL_Texture *texture_perso, SDL_Renderer *renderer, SDL_Rect *rectPerso, int *etatAnim, int direction) 
{
    int nbw = 4; //nombre de sprite sur une ligne
    int nbh = 4; //nombre de sprite sur une colonne

    SDL_Rect pos = {0, 0, 0, 0};
    SDL_QueryTexture(texture_perso, NULL, NULL, &pos.w, &pos.h); 
    SDL_Rect state = {(*etatAnim) * pos.w / nbw, direction * pos.h / nbh, pos.w / nbw, pos.h / nbh};

    SDL_RenderCopy(renderer, texture_perso, &state, rectPerso);

    *etatAnim += 1;
    *etatAnim = (*etatAnim) % nbw;
}


/**
 * @brief termine le jeu en fonction des conditions de victoire et de défaite
 * @param [in] rectPac SDL_Rect de pac-man
 * @param [in] tabRectPerso tableau contenant les SDL_Rect des personnages du jeu
 * @param [in] nbFan nombre de fantomes
 * @param [in] tabPerso tableau contenant les perso_t des personnages du jeu 
 * @param [in] WINDOWW largeur de la fenêtre de jeu
 * @param [in] WINDOWL hauteur de la fenêtre de jeu
 * @param [in] font police d'écriture du texte
 * @param [in] plateau tableau contenant les id des objets et personnages du jeu
 * @param [in] window fenêtre du jeu
 * @param [in] renderer renderer de la fenêtre de jeu
 * @param [in] w nombre de colonnes du plateau
 * @param [in] h nombre de lignes du plateau
 */ 
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

/**
 * @brief Affiche Game Over a la fin du jeu si perdu
 * @param [in] window fenetre de jeu
 * @param [in] renderer renderer de la fenetre
 * @param [in] font police d'ecriture utilisee
 */
void afficherTexteFin(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, SDL_Color couleur, char* text, int posx, int posy)
{
    SDL_Surface *text_surface = NULL;
    text_surface = TTF_RenderText_Blended(font, text, couleur);
    if (text_surface == NULL)
    {
        end_sdl(0, "Can't create text surface", window, renderer);
    }
    int W, H;
    SDL_GetWindowSize(window, &W, &H);
    SDL_Texture *text_texture = NULL;                                   
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); 
    if (text_texture == NULL)
    {
        end_sdl(0, "Can't create texture from surface", window, renderer);
    }

    SDL_FreeSurface(text_surface); 

    SDL_Rect pos = {posx, posy, 0, 0};                   
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); 
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);         

    SDL_DestroyTexture(text_texture);
}


/**
 * @brief Detecte une collision entre un fantome et pac_man grace aux rects
 * @param [in] rectPac ranctangle de Pac_man
 * @param [in] rectFan tableau de rectangle des fantomes
 * @param [in] nbFan nombre de fantome
 * @param [in] tabPerso tableau des perso
 * @return 
 *      - 0 pas de collision
 *      - 1 collision 
 */
int collision(SDL_Rect rectPac, SDL_Rect **rectFan, int nbFan, perso_t ** tabPerso)
{
    int col = 0;
    int i = 1;

    int ptHautGauchePac = rectPac.x;
    int ptHautDroitPac = rectPac.x + rectPac.w;
    int ptBasGauchePac = rectPac.y + rectPac.h;
    int ptYPac = rectPac.y;

    int ptHautDroitFan, ptHautGaucheFan, ptBasGaucheFan;
    int ptYFan;

    int superPac = tabPerso[0]->super;
    int j = 1;

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
                if(superPac == 0)
                {
                    col = 1;
                }
                else
                {
                    tabPerso[j]->super = 1;
                    tabPerso[j]->posX = 11;
                    tabPerso[j]->posY = 11;
                    rectFan[j]->x = rectFan[j]->w*23/2-rectFan[j]->w/2;
                    rectFan[j]->y = rectFan[j]->h*23/2-rectFan[j]->h/2;

                }
            }
        }
        else if (ptHautGaucheFan == ptHautGauchePac)
        {

            if ((ptYFan > ptYPac && ptYFan < ptBasGauchePac) ||
                (ptBasGaucheFan < ptBasGauchePac && ptBasGaucheFan > ptYPac))
            {
                if(superPac == 0)
                {
                    col = 1;
                }
                else
                {
                    tabPerso[j]->super = 1;
                    tabPerso[j]->posX = 11;
                    tabPerso[j]->posY = 11;
                    rectFan[j]->x = rectFan[j]->w*23/2-rectFan[j]->w/2;
                    rectFan[j]->y = rectFan[j]->h*23/2-rectFan[j]->h/2;
                }
            }
        }

        i++;
        j++;
    }

    return col;
}


/**
 * @brief animation fluide dans le deplacement des perso
 * @param [in] rectPerso tableau de ranctangle des perso
 * @param [in] nbPerso nombre de perso dans le jeu
 * @param [in] direction direction du perso
 */
void animeFluide(SDL_Rect **rectPerso, int nbPerso, int *direction, int w, int h)
{

    for (int k = 0; k < nbPerso; k++)
    {

        switch (direction[k])
        {
        case 1:
            rectPerso[k]->y = (rectPerso[k]->y + rectPerso[k]->h / 10)%h;
            break;
        case 2:
            rectPerso[k]->x = (w + rectPerso[k]->x -rectPerso[k]->w / 10)%w;
            break;
        case 3:
            rectPerso[k]->y = (h+rectPerso[k]->y -rectPerso[k]->h / 10)%h;
            break;
        case 4:
            rectPerso[k]->x = (rectPerso[k]->x +rectPerso[k]->w / 10)%w;
            break;
        default:
            break;
        }
    }
}


/**
 * @brief Selectionne la bonne texture de Pac man en fonction de super
 * @param [in] textPerso texture du perso dans le jeu
 * @param [in] textPersoNormal texture du perso en normal
 * @param [in] textPersoSuper texture du perso en super
 * @param [in] super 0 pac man n'est pas en super; 1 pac man est en super
 * @return texture de pac_man
 */
SDL_Texture* spriteSuperPerso(SDL_Texture **textPerso, SDL_Texture *textPersoNormal, SDL_Texture *textPersoSuper, int super)
{
    switch (super)
    {
    case 0:
        *textPerso = textPersoNormal;
        break;

    case 1:
        *textPerso = textPersoSuper;
        break;
    
    default:
        break;
    } 
    return *textPerso;  

}

/**
 * @brief détruit les textures, le renderer et la fenêtre du jeu
 * @param [in] textBlin texture de blinky affichée
 * @param [in] textBlinNormal texture de blinky dans son état normal
 * @param [in] textPac texture de pac-man affichée
 * @param [in] textPacNormal texture de pac-man dans son état normal
 * @param [in] textPacSuper texture de pac-man dans son état super
 * @param [in] textCly texture de clyde affichée
 * @param [in] textClyNormal texture de clyde dans son état normal
 * @param [in] textInk texture de inky affichée
 * @param [in] textInkNormal texture de inky dans son état normal
 * @param [in] textPin texture de pinky affichée 
 * @param [in] textPinNormal texture de pinky dans son état normal
 * @param [in] textFanSuper texture des fantomes dans leur état super
 * @param [in] renderer renderer de la fenêtre de jeu
 * @param [in] window fenêtre de jeu
 */ 
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

/**
 * @brief anime un fantome avec le bon état
 * @param [in] tabPerso tableau contenant les perso_t des personnages du jeu
 * @param [in] numFan numéro du fantome à animer
 * @param [in] textFantome texture du fantome affichée
 * @param [in] textFantomeNormal texture du fantome dans son état normal
 * @param [in] textFantomeSuper texture du fantome dans son état super
 * @param [in] etatAnim état de l'animation du fantome
 * @param [in] renderer renderer de la fenêtre du jeu
 * @param [in] tempsMortFantome temps pendant lequel un fantome n'est pas apparu après s'être fait tuer
 * @param [in] rectFan SDL_Rect du fantome à animer
 */ 
void animeFantome(perso_t** tabPerso, int numFan, SDL_Texture* textFantome, SDL_Texture* textFantomeNormal, SDL_Texture* textFantomSuper, int* etatAnim, SDL_Renderer* renderer, int* tempsMortFantome, SDL_Rect* rectFan)
{
    if (tabPerso[numFan]->posX != 0)
    {
        if (tabPerso[numFan]->super == 0)
        {
            textFantome = spriteSuperPerso(&textFantome, textFantomeNormal, textFantomSuper, tabPerso[0]->super);
            animePerso(textFantome, renderer, rectFan, etatAnim, tabPerso[numFan]->etat);
        }
        else
        {
            tempsMortFantome[numFan-1]++;
            *etatAnim += 1;
            *etatAnim = (*etatAnim) % 4;
        }
    }
}

/**
 * @brief anime pac-man avec le bon état 
 * @param [in] pac_man perso_t de pac-man
 * @param [in] textPac texture de pac-man affichée
 * @param [in] textPacNormal texture de pac-man dans état normal  
 * @param [in] textPacSuper texture de pac-man dans état super
 * @param [in] etatAnim état de l'animation de pac-man
 * @param [in] renderer renderer de la fenêtre de jeu
 * @param [in] rectPac SDL_Rect de pac-man
 */ 
void animePacMan(perso_t* pac_man, SDL_Texture* textPac, SDL_Texture* textPacNormal, SDL_Texture* textPacSuper, int* etatAnim, SDL_Renderer* renderer, SDL_Rect* rectPac)
{
    textPac = spriteSuperPerso(&textPac, textPacNormal, textPacSuper, pac_man->super);
    animePerso(textPac, renderer, rectPac, etatAnim, pac_man->etat);
}