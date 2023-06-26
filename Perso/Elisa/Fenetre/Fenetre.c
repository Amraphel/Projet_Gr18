#include <SDL2/SDL.h>
#include <stdio.h>

  //////////////////////////////////////
 //           Fenetres en X          //
//////////////////////////////////////

int main(int argc, char **argv) 
{
  (void)argc;
  (void)argv;

  SDL_bool
    program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
    paused = SDL_FALSE,                             // Booléen pour dire que le programme est en pause
    event_utile = SDL_FALSE;                        // Booléen pour savoir si on a trouvé un event traité 
    SDL_Event event;                                  // Evènement à traiter

  SDL_Window 
    *window_1 = NULL,                     // Future fenêtre de gauche
    *window_2 = NULL;                     // Future fenêtre de droite


/* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
    SDL_Log("Error : SDL initialisation - %s\n", 
      SDL_GetError());                // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }

/* Création de la fenêtre de gauche */
  window_1 = SDL_CreateWindow(
    "Fenêtre à gauche",                    // codage en utf8, donc accents possibles
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
  
/* Création de la fenêtre de droite */
  

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
              "Fenêtre à droite",                    // codage en utf8, donc accents possibles
              400, 0,                                // à droite de la fenêtre de gauche
              500, 300,                              // largeur = 500, hauteur = 300
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

/* Normalement, on devrait ici remplir les fenêtres... */
//SDL_Delay(2000);                           // Pause exprimée  en ms

/* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
SDL_DestroyWindow(window_2);               // la fenêtre 2  
SDL_DestroyWindow(window_1);               // la fenêtre 1     

SDL_Quit();                                // la SDL

  return 0;
}