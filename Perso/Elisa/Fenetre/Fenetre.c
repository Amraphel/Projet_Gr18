#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

//////////////////////////////////////
//            Jeu fenetre           //
//////////////////////////////////////

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
  {                                // Destruction si nécessaire du renderer
    SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
    renderer = NULL;
  }
  if (window != NULL)
  {                            // Destruction si nécessaire de la fenêtre
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

  SDL_FreeSurface(my_image); // la SDL_Surface ne sert que comme élément transitoire
  if (my_texture == NULL)
    end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

  return my_texture;
}

SDL_Window *initWindow(int x, int y, int w, int h)
{
  SDL_Window *window = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_Log("Error : SDL initialisation - %s\n",
            SDL_GetError());
    exit(EXIT_FAILURE);
  }
  window = SDL_CreateWindow(
      "Fenêtre",
      x, y,
      w, h,
      SDL_WINDOW_RESIZABLE);

  if (window == NULL)
  {
    SDL_Log("Error : SDL window creation - %s\n",
            SDL_GetError()); // échec de la création de la fenêtre
    SDL_Quit();              // On referme la SDL
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

  return renderer;
}

anime_t *createPerso(SDL_Renderer *renderer, SDL_Window *window)
{

  SDL_Texture *my_texture = load_texture_from_image("img/run.png", window, renderer);
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
        (window_dimensions.h - destination.h) * 5/ 6;

    animation->source = source;
    animation->window_dimensions = window_dimensions;
    animation->destination = destination;
    animation->state = state;
    animation->nbImages = nb_images;
    animation->texture = my_texture;
  }
  return animation;
}

void animePerso(anime_t *animation, SDL_Renderer *renderer)
{
  animation->state.x += animation->source.w / animation->nbImages; // On passe à la vignette suivante dans l'image

  if (animation->state.x >= animation->source.w - animation->source.w / animation->nbImages)
  {
    animation->state.x = 0;
  }

                  // La vignette qui suit celle de fin de ligne est                                      // Effacer l'image précédente avant de dessiner la nouvelle
  SDL_RenderCopy(renderer, animation->texture, // Préparation de l'affichage
                 &animation->state,
                 &animation->destination);
  SDL_RenderPresent(renderer); // Affichage

}

anime_t *createBack(SDL_Renderer *renderer, SDL_Window *window)
{

  SDL_Texture *my_texture = load_texture_from_image("img/Background/06_Forest.png", window, renderer);
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

    int nb_images = 250;                 // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
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
    for(int i = 0; i <= 3; i++)
    {
      animeBack(animeBackg, renderer, tab_fond);
      animeBack(animeBackg, renderer, tab_fond);
    }
    animePerso(animeSprite, renderer);
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

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  bool p_utilise = false;
  bool event_reduction_fenetre = false;
  /*INITIALISATION VARIABLES*/

  SDL_bool
      program_on = SDL_TRUE,   // Booléen pour dire que le programme doit continuer
      paused = SDL_FALSE,      // Booléen pour dire que le programme est en pause
      event_utile = SDL_FALSE, // Booléen pour savoir si on a trouvé un event traité
      event_souris = SDL_FALSE;

  SDL_Event event; // Evènement à traiter

  SDL_Renderer // Renderer
      *renderer = NULL,
      *renderer2 = NULL,
      *renderer3 = NULL,
      *renderer4 = NULL;

  SDL_Window // Initialisation des fenètres
      *window_1 = NULL,
      *window_2 = NULL,
      *window_3 = NULL,
      *window_4 = NULL;

  TTF_Font *font = NULL;

  /////////////////////////////////////////////////////////////////////////////////

  // Initialisation SDL TTF
  if (TTF_Init() < 0)
    end_sdl(0, "Couldn't initialize SDL TTF", window_1, renderer);

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_Log("Error : SDL initialisation - %s\n",
            SDL_GetError()); // l'initialisation de la SDL a échoué
    exit(EXIT_FAILURE);
  }

  // Création de la première fenetre et son renderer
  window_1 = initWindow(0, 0, 425, 50);
  renderer = initRenderer(window_1);

  // Initialisation text (font + color)
  font = TTF_OpenFont("./Front/BadComic-Regular.ttf", 20); // La police à charger, la taille désirée
  if (font == NULL)
  {
    end_sdl(0, "Can't load font", window_1, renderer);
  }

  SDL_Color color = {20, 0, 40, 255}; // la couleur du texte

  // Mise en place du renderer
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  // Création de la surface du text
  SDL_Surface *text_surface = NULL;
  text_surface = TTF_RenderText_Blended(font, "taper p ou f pour aller a la prochaine fenetre", color); // création du texte dans la surface
  if (text_surface == NULL)
  {
    end_sdl(0, "Can't create text surface", window_1, renderer);
  }

  // Création de la texture du text
  SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
  text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
  if (text_texture == NULL)
  {
    end_sdl(0, "Can't create texture from surface", window_1, renderer);
  }

  SDL_FreeSurface(text_surface); // la surface ne sert plus à rien

  SDL_Rect pos = {10, 0, 0, 0};                               // rectangle où le texte va être prositionné
  SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
  SDL_RenderCopy(renderer, text_texture, NULL, &pos);         // Ecriture du texte dans le renderer
  SDL_DestroyTexture(text_texture);                           // On n'a plus besoin de la texture avec le texte

  SDL_RenderPresent(renderer); // Affichage

  // EVENEMENT
  while (program_on)
  {
    event_utile = SDL_FALSE;

    while (!event_utile && SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:            // clique sur la x
        program_on = SDL_FALSE; // arrêt du programme
        event_utile = SDL_TRUE;
        break;

      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_p:
          if (!p_utilise)
          {
            window_2 = initWindow(500, 0, 500, 500);
            renderer2 = initRenderer(window_2);

            SDL_SetRenderDrawColor(renderer2, 255, 255, 255, 255);
            SDL_RenderClear(renderer2);

            SDL_Texture *my_texture = load_texture_from_image("./img/souris.png", window_2, renderer2);

            SDL_Rect pos = {0, 0, 0, 0};                              // rectangle où le texte va être prositionné
            SDL_QueryTexture(my_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
            SDL_RenderCopy(renderer2, my_texture, NULL, &pos);        // Ecriture du texte dans le renderer

            SDL_RenderPresent(renderer2); // Affichage
            int x = 0;
            int y = 0;

            while (!event_souris)
            {
              SDL_RenderClear(renderer2);
              SDL_Delay(150); // Petite pause
              x += 20;
              pos.x = x;
              if (x >= 300)
              {
                while (x > 0)
                {
                  SDL_RenderClear(renderer2);
                  SDL_Delay(150); // Petite pause
                  x -= 15;
                  y += 15;
                  pos.x = x;
                  pos.y = y;
                  SDL_QueryTexture(my_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
                  SDL_RenderCopy(renderer2, my_texture, NULL, &pos);        // Ecriture du texte dans le renderer
                  SDL_RenderPresent(renderer2);
                }
                event_souris = SDL_TRUE;
              }
              SDL_QueryTexture(my_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
              SDL_RenderCopy(renderer2, my_texture, NULL, &pos);        // Ecriture du texte dans le renderer
              SDL_RenderPresent(renderer2);
            }
            SDL_DestroyTexture(my_texture); // On n'a plus besoin de la texture avec le texte
          }

          SDL_Surface *text_surface = NULL;                                                                // la surface  (uniquement transitoire)
          text_surface = TTF_RenderText_Blended(font, "taper f pour aller a la prochaine fenetre", color); // création du texte dans la surface
          if (text_surface == NULL)
            end_sdl(0, "Can't create text surface", window_2, renderer2);

          SDL_Texture *text_texture = NULL;                                     // la texture qui contient le texte
          text_texture = SDL_CreateTextureFromSurface(renderer2, text_surface); // transfert de la surface à la texture
          if (text_texture == NULL)
            end_sdl(0, "Can't create texture from surface", window_2, renderer2);

          SDL_FreeSurface(text_surface); // la texture ne sert plus à rien

          SDL_Rect pos = {100, 250, 0, 0};                            // rectangle où le texte va être prositionné
          SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
          SDL_RenderCopy(renderer2, text_texture, NULL, &pos);        // Ecriture du texte dans le renderer
          SDL_DestroyTexture(text_texture);                           // On n'a plus besoin de la texture avec le texte

          SDL_RenderPresent(renderer2); // Affichage

          p_utilise = true;

          break;

        case SDLK_f: //  'f'
          if (!event_reduction_fenetre)
          {

            window_3 = initWindow(500, 100, 500, 500);
            renderer3 = initRenderer(window_3);

            SDL_SetRenderDrawColor(renderer3, 255, 112, 0, 255);
            SDL_RenderClear(renderer3);
            SDL_RenderPresent(renderer3);

            SDL_Delay(500);
            int h = 500, w = 500;
            int r = 255, g = 112, b = 0;

            while (h > 250 && w > 250)
            {
              w -= 50;
              h -= 50;
              r -= 8;
              g -= 12;
              b += 8;

              SDL_SetWindowSize(window_3, w, h);
              SDL_SetRenderDrawColor(renderer3, r, g, b, 255);
              SDL_RenderClear(renderer3);
              SDL_RenderPresent(renderer3);
              SDL_Delay(150);
            }
            while (h < 500 && w < 500)
            {
              w += 50;
              h += 50;
              r += 8;
              g += 12;
              b -= 8;

              SDL_SetWindowSize(window_3, w, h);
              SDL_SetRenderDrawColor(renderer3, r, g, b, 255);
              SDL_RenderClear(renderer3);
              SDL_RenderPresent(renderer3);
              SDL_Delay(150);
            }

            SDL_Surface *text_surface3 = NULL;                                                                // la surface  (uniquement transitoire)
            text_surface3 = TTF_RenderText_Blended(font, "taper e pour aller a la prochaine fenetre", color); // création du texte dans la surface
            if (text_surface3 == NULL)
              end_sdl(0, "Can't create text surface", window_3, renderer3);

            SDL_Texture *text_texture3 = NULL;                                      // la texture qui contient le texte
            text_texture3 = SDL_CreateTextureFromSurface(renderer3, text_surface3); // transfert de la surface à la texture
            if (text_texture3 == NULL)
              end_sdl(0, "Can't create texture from surface", window_3, renderer3);

            SDL_FreeSurface(text_surface3); // la texture ne sert plus à rien

            SDL_Rect pos3 = {75, 250, 0, 0};                               // rectangle où le texte va être prositionné
            SDL_QueryTexture(text_texture3, NULL, NULL, &pos3.w, &pos3.h); // récupération de la taille (w, h) du texte
            SDL_RenderCopy(renderer3, text_texture3, NULL, &pos3);         // Ecriture du texte dans le renderer
            SDL_DestroyTexture(text_texture3);                             // On n'a plus besoin de la texture avec le texte

            SDL_RenderPresent(renderer3); // Affichage
          }
          event_reduction_fenetre = true;
          break;

        case SDLK_e:
          window_4 = initWindow(500, 100, 500, 500);
          renderer4 = initRenderer(window_4);

          SDL_Rect fond[250];

          int fondW;
          int fondH;
          SDL_GetWindowSize(window_4, &fondW, &fondH);
          int k;
          for (k = 0; k < 250; k++)
          {
            fond[k].x = k * fondW / 250;
            fond[k].y = 0;
            fond[k].h = fondH;
            fond[k].w = fondW / 250;
          }

          SDL_SetRenderDrawColor(renderer4, 255, 255, 255, 255);

          // SDL_Texture *texture = load_texture_from_image("./img/run.png", window_4, renderer4);
          // animePerso(texture, window_4, renderer4);
          anime_t *animationBack = createBack(renderer4, window_4);
          anime_t *animeP = createPerso(renderer4, window_4);
          SDL_RenderPresent(renderer4);

          animePerso(animeP, renderer4);

          int speed = 10000;
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

                case SDLK_ESCAPE:
                case SDLK_q:
                  program_on = 0;
                  break;
                default:
                  break;
                }
                anime(animeP, animationBack, renderer4, fond, 0);
                break;
              }
            }

            if (i == 0)
            {
              anime(animeP, animationBack, renderer4, fond, 1);
            }
            i = (i + 1) % speed;
          }

          free(animeP);
          end_sdl(1, "Normal ending", window_4, renderer4);
          return EXIT_SUCCESS;

          break;

        case SDLK_SPACE:
          break;

        case SDLK_ESCAPE: // 'escape' ou 'q', arret du programme
        case SDLK_q:
          program_on = 0;
          event_utile = SDL_TRUE;
          break;

        default:
          break;
        }
        break;

      default:
        break;
      }
    }

    SDL_Delay(50); // Petite pause
  }

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
  SDL_DestroyWindow(window_2); // la fenêtre 2
  SDL_DestroyWindow(window_3);
  SDL_DestroyWindow(window_4);

  // SDL_DestroyWindow(window_1);               // la fenêtre 1
  TTF_Quit();
  IMG_Quit();
  SDL_Quit(); // la SDL

  return 0;
}