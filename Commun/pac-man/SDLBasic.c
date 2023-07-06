#include "SDLBasic.h"

/**
 * @brief fonction qui permet de quitter la SDL
 * @param [in] ok int indiquant s'il y a une erreur
 * @param [in] msg message d'erreur à afficher
 * @param [in] window fenêtre d'affichage
 * @param [in] renderer renderer de la fenêtre de jeu
 */ 
void end_sdl(char ok,
             char const *msg,
             SDL_Window *window,
             SDL_Renderer *renderer)
{
    char msg_formated[255];
    int l;

    if (!ok)
    {
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief permet de créer une fenêtre de dimension donnée
 * @param [in] x abscisse du coin haut gauche de la fenêtre à créer
 * @param [in] y ordonnée du coin haut gauche de la fenêtre à créer
 * @param [in] w largeur de la fenêtre à créer
 * @param [in] h hauteur de la fenêtre à créer
 * @return la fenêtre créée
 */ 

SDL_Window *initWindow(int x, int y, int w, int h)
{
    SDL_Window *window = NULL;

    window = SDL_CreateWindow(
        "Fenêtre",
        x, y,
        w, h,
        SDL_WINDOW_RESIZABLE);

    if (window == NULL)
    {
        SDL_Log("Error : SDL window creation - %s\n",
                SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    return window;
}

/**
 * @brief créé le renderer dans le fenêtre de jeu
 * @param [in] window fenêtre de jeu
 * @return le renderer créé
 */ 
SDL_Renderer *initRenderer(SDL_Window *window)
{
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return renderer;
}

/**
 * @brief charge une image sur une texture
 * @param [in] file_image_name nom du fichier contenant l'image
 * @param [in] window fenêtre de jeu
 * @param [in] renderer renderer de la fenêtre de jeu
 * @return la texture créée 
 */ 
SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface *my_image = NULL;
    SDL_Texture *my_texture = NULL;

    my_image = IMG_Load(file_image_name);
    if (my_image == NULL)
        end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image);
    SDL_FreeSurface(my_image);
    if (my_texture == NULL)
        end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

