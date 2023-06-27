#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>

typedef struct anime
{
    SDL_Rect source;
    SDL_Rect window_dimensions;
    SDL_Rect destination;
    SDL_Rect state;
    int nbImages;
    SDL_Texture *texture;
} anime_t;

void end_sdl(char ok,            // fin normale : ok = 0 ; anormale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
{ // renderer à fermer
    char msg_formated[255];
    int l;

    if (!ok)
    { // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
    {                                  // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL)
    {                              // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
        window = NULL;
    }

    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}

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

anime_t *createFish(SDL_Renderer *renderer, SDL_Window *window)
{

    SDL_Texture *my_texture = load_texture_from_image("./sources/Fish_sprite_X200.png", window, renderer);
    anime_t *animation = malloc(sizeof(anime_t));
    if (animation)
    {

        SDL_Rect
            source = {0},            // Rectangle définissant la zone totale de la planche
            window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
            state = {0};             // Rectangle de la vignette en cours dans la planche

        SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                          &window_dimensions.w,
                          &window_dimensions.h);
        SDL_QueryTexture(my_texture, // Récupération des dimensions de l'image
                         NULL, NULL,
                         &source.w, &source.h);

        /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

        int nb_images = 6;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
        float zoom = 1;                      // zoom, car ces images sont un peu petites
        int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image, marche car la planche est bien réglée
            offset_y = source.h;             // La hauteur d'une vignette de l'image, marche car la planche est bien réglée

        state.x = 0;        // La première vignette est en début de ligne
        state.y = 0;        // On s'intéresse à la 4ème ligne, le bonhomme qui court
        state.w = offset_x; // Largeur de la vignette
        state.h = offset_y; // Hauteur de la vignette

        destination.w = offset_x * zoom; // Largeur du sprite à l'écran
        destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

        destination.y = // La course se fait en milieu d'écran (en vertical)
            (window_dimensions.h - destination.h) / 2;

        // int speed = 6;
        // for (int x = 0; x < window_dimensions.w - destination.w; x += speed)
        // {
        //     destination.x = x;   // Position en x pour l'affichage du sprite
        //     state.x += offset_x; // On passe à la vignette suivante dans l'image
        //     state.x %= source.w; // La vignette qui suit celle de fin de ligne est
        //                          // celle de début de ligne

        //     SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
        //     SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
        //                    &state,
        //                    &destination);
        //     SDL_RenderPresent(renderer); // Affichage
        //     SDL_Delay(80);               // Pause en ms
        // }
        // SDL_RenderClear(renderer);

        animation->source = source;
        animation->window_dimensions = window_dimensions;
        animation->destination = destination;
        animation->state = state;
        animation->nbImages = nb_images;
        animation->texture = my_texture;
    }
    return animation;
}

void animeFish(anime_t *animation, SDL_Renderer *renderer)
{
    animation->state.x += animation->source.w / animation->nbImages; // On passe à la vignette suivante dans l'image
    animation->state.x %= animation->source.w;                       // La vignette qui suit celle de fin de ligne est
    SDL_RenderClear(renderer);                                       // Effacer l'image précédente avant de dessiner la nouvelle
    SDL_RenderCopy(renderer, animation->texture,                     // Préparation de l'affichage
                   &animation->state,
                   &animation->destination);
    SDL_RenderPresent(renderer); // Affichage
}

void moveFish(SDL_Renderer *renderer, anime_t *animation, int dir, int w, int h)
{
    SDL_SetRenderDrawColor(renderer, 0, 94, 184, 255);
    SDL_RenderClear(renderer);
    switch (dir)
    {
    case 1:
        animation->destination.x = animation->destination.x - 10;
        break;
    case 2:
        animation->destination.x = animation->destination.x + 10;
        break;
    case 3:
        animation->destination.y =  animation->destination.y - 10;
        break;
    case 4:
        animation->destination.y = animation->destination.y + 10;
        break;
    default:
        break;
    }

    SDL_RenderCopy(renderer, animation->texture, // Préparation de l'affichage
                   &animation->state,
                   &animation->destination);
    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    int w;
    int h;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        end_sdl(0, "ERROR SDL INIT", window, renderer);
    getMaxSize(&w, &h);
    SDL_GetCurrentDisplayMode(0, &screen);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, w * 0.66,
                              h * 0.66,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    SDL_Rect fond;
    fond.x = 0;
    fond.y = 0;
    int fondW;
    int fondH;
    SDL_GetWindowSize(window, &fondW, &fondH);
    fond.w = fondW;
    fond.h = fondH;

    SDL_SetRenderDrawColor(renderer, 0, 94, 184, 255);
    SDL_RenderFillRect(renderer, &fond);

    anime_t *animation = createFish(renderer, window);
    SDL_RenderPresent(renderer);
    SDL_bool program_on = SDL_TRUE;
    SDL_bool event_utile;
    SDL_Event event;
    while (program_on)
    { // La boucle des évènements
        event_utile = SDL_FALSE;
        while (!event_utile && SDL_PollEvent(&event))
        {
            animeFish(animation, renderer);
            switch (event.type)
            {
            case SDL_QUIT:
                program_on = SDL_FALSE;
                event_utile = SDL_TRUE;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_p:
                case SDLK_LEFT:
                    moveFish(renderer, animation, 1, fondW, fondH);
                    event_utile = SDL_TRUE;
                    break;
                case SDLK_RIGHT:
                    moveFish(renderer, animation, 2, fondW, fondH);
                    event_utile = SDL_TRUE;
                    break;
                case SDLK_UP:
                    moveFish(renderer, animation, 3, fondW, fondH);
                    break;
                case SDLK_DOWN:
                    moveFish(renderer, animation, 4, fondW, fondH);
                    break;
                case SDLK_ESCAPE:
                case SDLK_q:
                    program_on = 0;
                    event_utile = SDL_TRUE;
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }

    free(animation);
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}