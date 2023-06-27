 #include <SDL2/SDL.h>
     #include <stdio.h>

     /************************************/
     /*  exemple de création de fenêtres */
     /************************************/

     int main(int argc, char **argv) {
       (void)argc;
       (void)argv;
       int i;

       SDL_Window* tab_Win[10];   
       SDL_Renderer* tab_Ren[10];                  // Future fenêtre de droite

       /* Initialisation de la SDL  + gestion de l'échec possible */
       if (SDL_Init(SDL_INIT_VIDEO) != 0) {
     SDL_Log("Error : SDL initialisation - %s\n", 
                  SDL_GetError());                // l'initialisation de la SDL a échoué 
     exit(EXIT_FAILURE);
       }

       for (i=1; i<11; i++)
       {
        int x;
        int y;
        if (i<=4)
        {
            x=200*i;
            y=30;
        }
        else if (i<=7)
        {
            x=(8-i)*200;
            y=(i-4)*200+30;
        }
        else
        {
            x=200*(i-6);
            y=630;
        }
        SDL_Window* window = SDL_CreateWindow("", x, y, 200, 200, SDL_WINDOW_RESIZABLE); 
        if (window == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", 
                 SDL_GetError());                 // échec de la création de la fenêtre
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
        }                // redimensionnable
        SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        tab_Win[i]=window;
        tab_Ren[i]=renderer;
        SDL_Delay(1000);
       }
       SDL_Delay(10000);
        for (i=9;i>0;i--)
        {
            SDL_DestroyRenderer(tab_Ren[i]);
            SDL_DestroyWindow(tab_Win[i]);
        }  

        SDL_Quit();                                // la SDL
 
       return 0;
     }
