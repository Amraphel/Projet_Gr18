#include <SDL2/SDL.h>
#include <stdio.h>

     /************************************/
     /*  exemple de création de fenêtres */
     /************************************/

int getMaxSize(int* w, int* h){
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

void destroyWin(SDL_Window** window_tab , int taille){
    int i;
    for(i=0; i<taille; i++){
        SDL_DestroyWindow(window_tab[i]);
    }
    free(window_tab);
    window_tab=NULL;
}

void destroyRen(SDL_Renderer** renderer_tab , int taille){
    int i;
    for(i=0; i<taille; i++){
        SDL_DestroyRenderer(renderer_tab[i]);
    }
    free(renderer_tab);
    renderer_tab=NULL;
}

void moveWin(SDL_Window** window_tab,int iter, int taille){
    int i;
    int x;
    int y;
    for(i=0; i<taille; i++){
        if(iter<15){
            SDL_GetWindowPosition(window_tab[i], &x, &y);
            SDL_SetWindowPosition(window_tab[i],x, y-70);

        } else{
            SDL_GetWindowPosition(window_tab[i], &x, &y);
            switch (i)
            {
            case 0:
                x=x+30;
                break;
            case 1:
                x=x+30;
                y=y+30;
                break;
            case 2:
                y=y+30;
                break;
            case 3:
                x=x-30;
                y=y+30;
                break;
            case 4:
                x=x+30;
                y=y-30;
                break;
            case 5:
                x=x-30;
                y=y-30;
                break;
            case 6:
                y=y-30;
                break;
            case 7:
                x=x-30;
                break;
            default:
                break;
            }
            SDL_SetWindowPosition(window_tab[i],x, y);
        }

    }
    SDL_Delay(100);
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    int w, h;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", 
                SDL_GetError());                // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
    }


    SDL_Window** window_tab =  malloc(sizeof(SDL_Window*)*8); 
    SDL_Renderer** renderer_tab =  malloc(sizeof(SDL_Renderer*)*8);                   // Future fenêtre de droite
    getMaxSize(&w,&h);

    int i;
    for(i=0; i<8; i++){
        SDL_Window* window = SDL_CreateWindow("", w/2, (h-200), 200, 200, SDL_WINDOW_RESIZABLE);
        if (window == NULL) {
            SDL_Log("Error : SDL window 1 creation - %s\n", 
                SDL_GetError());               
            SDL_Quit();                              
            exit(EXIT_FAILURE);
        }

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        window_tab[i]=window;
        renderer_tab[i]=renderer;

    }

    i=0;
    while(i<30){
        moveWin(window_tab,i,8);
        i++;
    }                   
        
    destroyWin(window_tab, 8);
    destroyRen(renderer_tab, 8);


    SDL_Quit();                                
 
    return 0;
}