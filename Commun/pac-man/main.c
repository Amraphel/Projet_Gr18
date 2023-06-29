#include "affichage.h"
#include "fantome.h"
#include "plateau.h"


#define WINDOWL 700
#define WINDOWW 700

int main()
{
    int w;
    int h;
    int ** plateau=   loadPlateau("./source/lvl1.txt", &w, &h);
    printPlateau(plateau,w,h);
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window *window = initWindow(200, 100, WINDOWW, WINDOWL);
    SDL_Renderer *renderer = initRenderer(window);
    SDL_Rect** tabRect = createTabRect(window,w,h);
        perso_t * Pac_man =initPac_man(plateau,w,h);
    afficherPlateau(tabRect,plateau,w,h,window,renderer);
    afficherPerso(Pac_man,window,renderer,tabRect);
    //void movePersoInPlateau(plateau, perso.posX, perso.posY, w, h, 1);



    SDL_RenderPresent(renderer);
    // while ((plateau[&Pac_man->posx][&Pac_man->posy]<200) && (!gom_exist(plateau, w,h))) 
    // {
        
    //     SDL_WaitEvent(&event);
    //     switch(event.type)
    //     {
    //         case SDL_KEYDOWN:
    //         switch(event.key.keysym.sym)
    //         {
    //             case SDLK_DOWN:
    //             {   
    //                 movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, 99, 3);
    //             }    
    //             break;
    //             case SDLK_DOWN:
    //             if(movePossible(plateau, &Pac_man->posX,&Pac_man->posY, 1))
    //             {   
    //                 movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, 99, 1);
    //             }    
    //             break;        
    //             case SDLK_RIGHT:
    //             if(movePossible(plateau, &Pac_man->posX,&Pac_man->posY, 4))
    //             {  
    //                 movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, 99, 4);
    //             }    
    //             break;        
    //             case SDLK_LEFT:
    //             if(movePossible(plateau, &Pac_man->posX,&Pac_man->posY, 2))
    //             {  
    //                 movePersoInPlateau(plateau, &Pac_man->posX, &Pac_man->posY, 99, 2);
    //             }    
    //             break;
    //             afficherPlateau(tabRect,plateau,w,h,window,renderer);
    //             // mouv_Pac_man(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer * renderer, &Pac_man->posX, &Pac_man->posY);
    //             SDL_RenderPresent(renderer);        
    //         }
    //         break;
    //     }
    // } 
    SDL_Delay(6000);
    end_sdl(1, "Normal ending", window, renderer);

    return 0;
}