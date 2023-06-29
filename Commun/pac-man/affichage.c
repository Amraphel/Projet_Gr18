#include "affichage.h"

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

SDL_Renderer *initRenderer(SDL_Window *window)
{
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    }
    SDL_SetRenderDrawColor(renderer, 65, 105, 225, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return renderer;
}

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

SDL_Rect **createTabRect(SDL_Window *window, int w, int h)
{
    SDL_Rect ** tabRect = malloc(sizeof(SDL_Rect *)*w);
    int fondW, fondH;
    SDL_GetWindowSize(window, &fondW, &fondH);
    int larg = fondW/w;
    int haut= fondH/h;
        for (int i = 0; i < w; i++)
    {

         SDL_Rect * ligneRect = malloc(sizeof(SDL_Rect )*w);
         tabRect[i]=ligneRect;
        for (int j = 0; j < h; j++)
        {
            SDL_Rect rect;
            rect.x = i*larg;
            rect.y= j* haut;
            rect.w=larg;
            rect.h=haut;
            tabRect[i][j]=rect;
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
            if (plateau[j][i] != 0)
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

                state.x = (plateau[j][i]-1) * offset_x;
                state.y = 0;
                state.w = offset_x;
                state.h = offset_y;


                SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                               &state,
                               &tabRect[i][j]);
            }
        }
    }
    SDL_RenderPresent(renderer);
}