#include <SDL2/SDL_image.h> 
#include <stdio.h>          
                            

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

SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface *my_image = NULL;   // Variable de passage
    SDL_Texture *my_texture = NULL; // La texture

    my_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
                                          // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
                                          // uniquement possible si l'image est au format bmp */
    if (my_image == NULL)
        end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire
    if (my_texture == NULL)
        end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, my_texture,
                   &source,
                   &destination); // Création de l'élément à afficher
 // Affichage
}

void play_with_texture_4(SDL_Texture *my_texture,
                         SDL_Window *window,
                         SDL_Renderer *renderer)
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



    int nb_images = 6;
    float zoom = 2;                      // zoom, car ces images sont un peu petites
    int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h;             // La hauteur d'une vignette de l'image, marche car la planche est bien réglée
    SDL_Event event;
    state.x = 0;        // La première vignette est en début de ligne
    state.y = 0;       
    state.w = offset_x; // Largeur de la vignette
    state.h = offset_y; // Hauteur de la vignette

    destination.w = offset_x * zoom; // Largeur du sprite à l'écran
    destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

    destination.y = // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h - destination.h) / 2;
   
    SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
    SDL_Texture *my_background = load_texture_from_image("background_ocean.png", window, renderer);
    play_with_texture_1(my_background, window, renderer);
    SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                       &state,
                       &destination);
    SDL_RenderPresent(renderer); // Affichage
    while (destination.x<window_dimensions.w-destination.w)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
                destination.y=destination.y-5;
                state.x += offset_x; // On passe à la vignette suivante dans l'image
                state.x %= source.w; // La vignette qui suit celle de fin de ligne est
                             // celle de début de ligne
                my_background = load_texture_from_image("background_ocean.png", window, renderer);
                play_with_texture_1(my_background, window, renderer);
                SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                       &state,
                       &destination);
                SDL_RenderPresent(renderer); // Affichage
                break;
                case SDLK_DOWN:
                SDL_RenderClear(renderer);           
                destination.y=destination.y+5;
                state.x += offset_x; 
                state.x %= source.w; 
                             
                my_background = load_texture_from_image("background_ocean.png", window, renderer);
                play_with_texture_1(my_background, window, renderer);
                SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                       &state,
                       &destination);
                SDL_RenderPresent(renderer); // Affichage
                break;
                case SDLK_RIGHT:
                SDL_RenderClear(renderer);           
                destination.x=destination.x+5;
                state.x += offset_x; 
                state.x %= source.w; 
                my_background = load_texture_from_image("background_ocean.png", window, renderer);
                play_with_texture_1(my_background, window, renderer);
                SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                       &state,
                       &destination);
                SDL_RenderPresent(renderer); // Affichage
                break;
                case SDLK_LEFT:
                SDL_RenderClear(renderer);           
                destination.x=destination.x-5;
                state.x += offset_x; 
                state.x %= source.w; 
                my_background = load_texture_from_image("background_ocean.png", window, renderer);
                play_with_texture_1(my_background, window, renderer);
                SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                       &state,
                       &destination);
                SDL_RenderPresent(renderer); // Affichage
                break;
            }
            break;
        }
    }
    SDL_RenderClear(renderer); // Effacer la fenêtre avant de rendre la main
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    SDL_Window
        *window_1 = NULL;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }
    window_1 = SDL_CreateWindow("", 0, 0, 1000, 1000, SDL_WINDOW_RESIZABLE);
    if (window_1 == NULL)
    {
        SDL_Log("Error : SDL window 1 creation - %s\n",
                SDL_GetError()); // échec de la création de la fenêtre
        SDL_Quit();              // On referme la SDL
        exit(EXIT_FAILURE);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window_1, -1, 0);
    SDL_Texture *my_texture = load_texture_from_image("Fish_sprite.png", window_1, renderer);
    play_with_texture_4(my_texture, window_1, renderer);
    SDL_DestroyTexture(my_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    IMG_Quit();
}
