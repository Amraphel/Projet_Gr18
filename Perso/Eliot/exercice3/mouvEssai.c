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

        animation->source = source;
        animation->window_dimensions = window_dimensions;
        animation->destination = destination;
        animation->state = state;
        animation->nbImages = nb_images;
        animation->texture = my_texture;
    }
    return animation;
}

anime_t *createBack(SDL_Renderer *renderer, SDL_Window *window)
{

    SDL_Texture *my_texture = load_texture_from_image("./sources/Background/Midday_Plants.PNG", window, renderer);
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

        int nb_images = 250;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
        float zoom = 1;                      // zoom, car ces images sont un peu petites
        int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image, marche car la planche est bien réglée
            offset_y = source.h;             // La hauteur d'une vignette de l'image, marche car la planche est bien réglée

        state.x = 0;        // La première vignette est en début de ligne
        state.y = 0;        // On s'intéresse à la 4ème ligne, le bonhomme qui court
        state.w = offset_x; // Largeur de la vignette
        state.h = offset_y; // Hauteur de la vignette

        destination.w = offset_x * zoom; // Largeur du sprite à l'écran
        destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

        destination.y = 0;

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
    animation->state.x %= animation->source.w;                       // La vignette qui suit celle de fin de ligne est                                      // Effacer l'image précédente avant de dessiner la nouvelle
    SDL_RenderCopy(renderer, animation->texture,                     // Préparation de l'affichage
                   &animation->state,
                   &animation->destination);
    SDL_RenderPresent(renderer); // Affichage
}

void animeBack(anime_t *animation, SDL_Renderer *renderer, SDL_Rect *tab_fond)
{
    animation->state.x += animation->source.w / animation->nbImages; // On passe à la vignette suivante dans l'image
    animation->state.x %= animation->source.w;                       // La vignette qui suit celle de fin de ligne est
    int x = animation->state.x;
    SDL_RenderClear(renderer);
    int i;
    for (i = 0; i < 250; i++)
    {
        SDL_RenderCopy(renderer, animation->texture, // Préparation de l'affichage
                       &animation->state,
                       &tab_fond[i]);
        animation->state.x += animation->source.w / animation->nbImages;
        animation->state.x %= animation->source.w;   
    }
    animation->state.x = x;
}

void anime(anime_t *animeSprite, anime_t *animeBackg, SDL_Renderer *renderer, SDL_Rect *tab_fond, int act)
{
    if (act == 1)
    {
        animeBack(animeBackg, renderer, tab_fond);
        animeBack(animeBackg, renderer, tab_fond);
        animeBack(animeBackg, renderer, tab_fond);
        animeFish(animeSprite, renderer);
    }
    else
    {
        int x = animeBackg->state.x;
        SDL_RenderClear(renderer);
        int i;
        for (i = 0; i < 250; i++)
        {
            SDL_RenderCopy(renderer, animeBackg->texture, // Préparation de l'affichage
                           &animeBackg->state,
                           &tab_fond[i]);
            animeBackg->state.x += animeBackg->source.w / animeBackg->nbImages;
            animeBackg->state.x %= animeBackg->source.w;   
        }
        animeBackg->state.x = x;

        SDL_RenderCopy(renderer, animeSprite->texture, // Préparation de l'affichage
                       &animeSprite->state,
                       &animeSprite->destination);
        SDL_RenderPresent(renderer); // Affichage
    }
}

void moveFish(anime_t *animation, int dir, int w, int h)
{
    // SDL_SetRenderDrawColor(renderer, 0, 94, 184, 255);
    // SDL_RenderClear(renderer);
    switch (dir)
    {
    case 1:
        if (animation->destination.x + animation->destination.w < 0)
        {
            animation->destination.x = w;
        }
        else
        {
            animation->destination.x = animation->destination.x - 10;
        }

        break;
    case 2:
        if (animation->destination.x > w)
        {
            animation->destination.x = 0;
        }
        else
        {
            animation->destination.x = (animation->destination.x + 10);
        }

        break;
    case 3:
        if (animation->destination.y + animation->destination.w < 0)
        {
            animation->destination.y = h;
        }
        else
        {
            animation->destination.y = animation->destination.y - 10;
        }

        break;
    case 4:
        if (animation->destination.y > h)
        {
            animation->destination.y = 0;
        }
        else
        {
            animation->destination.y = (animation->destination.y + 10);
        }
        break;
    default:
        break;
    }

    // SDL_RenderCopy(renderer, animation->texture, // Préparation de l'affichage
    //                &animation->state,
    //                &animation->destination);
    // SDL_RenderPresent(renderer);
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

    SDL_Rect fond[250];


    int fondW;
    int fondH;
    SDL_GetWindowSize(window, &fondW, &fondH);
    int k;
    for(k=0; k<250; k++){
        fond[k].x=k*fondW/250;
        fond[k].y=0;
        fond[k].h=fondH;
        fond[k].w=fondW/250;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    anime_t *animation = createFish(renderer, window);
    anime_t *animationBack = createBack(renderer, window);
    SDL_RenderPresent(renderer);

    SDL_bool program_on = SDL_TRUE;

    SDL_Event event;
    animeFish(animation, renderer);
    int speed = 100000;
    int i = 0;
    while (program_on)
    { // La boucle des évènements
        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                program_on = SDL_FALSE;
                break;
            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    moveFish(animation, 1, fondW, fondH);
                    break;
                case SDLK_RIGHT:
                    moveFish(animation, 2, fondW, fondH);
                    break;
                case SDLK_UP:
                    moveFish(animation, 3, fondW, fondH);
                    break;
                case SDLK_DOWN:
                    moveFish(animation, 4, fondW, fondH);
                    break;
                case SDLK_ESCAPE:
                case SDLK_q:
                    program_on = 0;
                    break;
                default:
                    break;
                }
                anime(animation, animationBack, renderer, fond, 0);
                break;
            }
        }

        if (i == 0)
        {
            anime(animation, animationBack, renderer, fond, 1);
        }
        i = (i + 1) % speed;
    }

    free(animation);
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}