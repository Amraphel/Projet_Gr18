#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>


  //////////////////////////////////////
 //            Jeu fenetre           //
//////////////////////////////////////

void end_sdl(char ok,                                               // fin normale : ok = 0 ; anormale ok = 1
  char const* msg,                                       // message à afficher
  SDL_Window* window,                                    // fenêtre à fermer
  SDL_Renderer* renderer) 
{                              // renderer à fermer
  char msg_formated[255];                                            
  int l;                                                     
                                      
  if (!ok) {                                                        // Affichage de ce qui ne va pas
    strncpy(msg_formated, msg, 250);                                         
    l = strlen(msg_formated);                                            
    strcpy(msg_formated + l, " : %s\n");                                                                       
    SDL_Log(msg_formated, SDL_GetError());                                   
  }                                                          
                                      
  if (renderer != NULL) {                                           // Destruction si nécessaire du renderer
    SDL_DestroyRenderer(renderer);                                  // Attention : on suppose que les NULL sont maintenus !!
    renderer = NULL;
  }
  if (window != NULL)   {                                           // Destruction si nécessaire de la fenêtre
    SDL_DestroyWindow(window);                                      // Attention : on suppose que les NULL sont maintenus !!
    window= NULL;
  }
                                      
  SDL_Quit();                                                    
                                      
  if (!ok) {                                       // On quitte si cela ne va pas            
    exit(EXIT_FAILURE);                                                  
  }                                                          
}

int main(int argc, char **argv) 
{
  (void)argc;
  (void)argv;

  SDL_bool
    program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
    paused = SDL_FALSE,                             // Booléen pour dire que le programme est en pause
    event_utile = SDL_FALSE;                        // Booléen pour savoir si on a trouvé un event traité 
    SDL_Event event;                                // Evènement à traiter
    SDL_Renderer* renderer = NULL;                  // Renderer

  SDL_Window                                        // Initialisation des fenètres
    *window_1 = NULL,                     
    *window_2 = NULL;                     

  // Vérification SDL TTF bien initialisée
  if (TTF_Init() < 0) end_sdl(0, "Couldn't initialize SDL TTF", window_1, renderer); 

  // Création de la police + vérification
  TTF_Font* font = NULL;                                               // la variable 'police de caractère'
  font = TTF_OpenFont("./Front/BadComic-Regular.ttf", 28);                     // La police à charger, la taille désirée
  if (font == NULL) end_sdl(0, "Can't load font", window_1, renderer);

  // Initialisation de la SDL  + gestion de l'échec possible 
  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
    SDL_Log("Error : SDL initialisation - %s\n", 
      SDL_GetError());                // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }


  // Création de la prmière fenetre + vérfication 
  window_1 = SDL_CreateWindow(
    "Fenêtre 1",                    // codage en utf8, donc accents possibles
    0, 0,                                  // coin haut gauche en haut gauche de l'écran
    400, 300,                              // largeur = 400, hauteur = 300
    SDL_WINDOW_RESIZABLE);                 // redimensionnable

  if (window_1 == NULL) 
  {
    SDL_Log("Error : SDL window 1 creation - %s\n", 
      SDL_GetError());                 // échec de la création de la fenêtre
    SDL_Quit();                              // On referme la SDL       
    exit(EXIT_FAILURE);
  }

  // Création du renderer de la fenetre 1
    renderer = SDL_CreateRenderer(window_1, -1,
                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window_1, renderer);

  // contenue du renderer + verification 
  SDL_Color color = {20, 0, 40, 255};                                  // la couleur du texte
  
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  SDL_Surface* text_surface = NULL;                                    // la surface  (uniquement transitoire)
  text_surface = TTF_RenderText_Blended(font, "taper p pour aller a la prochaine fenetre", color); // création du texte dans la surface 
  if (text_surface == NULL) end_sdl(0, "Can't create text surface", window_1, renderer);

  SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte
  text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
  if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window_1, renderer);
  
  SDL_FreeSurface(text_surface);                                       // la texture ne sert plus à rien

  SDL_Rect pos = {0, 0, 0, 0};                                         // rectangle où le texte va être prositionné
  SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
  SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer   
  SDL_DestroyTexture(text_texture);                                    // On n'a plus besoin de la texture avec le texte

  SDL_RenderPresent(renderer);                                         // Affichage 
  
//EVENEMENT
  while (program_on) {                              // La boucle des évènements
    event_utile = SDL_FALSE;
    while(!event_utile && SDL_PollEvent(&event)) {  // Tant que on n'a pas trouvé d'évènement utile
                                                    // et la file des évènements stockés n'est pas vide et qu'on n'a pas
                            // terminé le programme Défiler l'élément en tête de file dans 'event'
      switch (event.type) {                         // En fonction de la valeur du type de cet évènement
        case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
          program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
          event_utile = SDL_TRUE;
        break;

        case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée
                            // comme la valeur du type est SDL_Keydown, dans la partie 'union' de
                            // l'event, plusieurs champs deviennent pertinents   
          switch (event.key.keysym.sym) {             // la touche appuyée est ...
            case SDLK_p:                                // 'p'
              window_2 = SDL_CreateWindow(
              "Fenêtre 2",                    // codage en utf8, donc accents possibles
              500, 0,                                // à droite de la fenêtre de gauche
              500, 500,                              // largeur = 500, hauteur = 300
              0);

              if (window_2 == NULL) 
              {
                /* L'init de la SDL : OK
                fenêtre 1 :OK
                fenêtre 2 : échec */
                SDL_Log("Error : SDL window 2 creation - %s\n", 
                  SDL_GetError());                 // échec de la création de la deuxième fenêtre 
                SDL_DestroyWindow(window_1);             // la première fenétre (qui elle a été créée) doit être détruite
                SDL_Quit();
                exit(EXIT_FAILURE);
              }



            break;
            case SDLK_SPACE:                            // ou 'SPC'
              paused = !paused;                         // basculement pause/unpause
              event_utile = SDL_TRUE;
            break;

            case SDLK_ESCAPE:                           // 'ESCAPE'  
            case SDLK_q:                                // ou 'q'
              program_on = 0;                           // 'escape' ou 'q', d'autres façons de quitter le programme                     
              event_utile = SDL_TRUE;
            break;
            
            default:                                    // Une touche appuyée qu'on ne traite pas
            break;
          }
        break;
        
        default:                                      // Les évènements qu'on n'a pas envisagé
        break;
      }
    }
    
    SDL_Delay(50);                                  // Petite pause
  }

/* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
SDL_DestroyWindow(window_2);               // la fenêtre 2  
//SDL_DestroyWindow(window_1);               // la fenêtre 1     
TTF_Quit();
SDL_Quit();                                // la SDL

  return 0;
}