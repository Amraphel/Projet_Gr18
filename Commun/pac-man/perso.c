#include "perso.h"
perso_t* initPac_man(int ** plateau){
    perso_t* Pac_man = malloc(sizeof(perso_t));
    Pac_man->id=99;
    coordPlat(plateau, w, h, Pac_man->id, &Pac_man->posx, &Pac_man->posy);

}


void mouv_Pac_man(SDL_Texture *my_texture,
                         SDL_Window *window,
                         SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            
        window_dimensions = {0}, 
        destination = {0},       
        state = {0};             

    SDL_GetWindowSize(window, 
                      &window_dimensions.w,
                      &window_dimensions.h);
    SDL_QueryTexture(my_texture, 
                     NULL, NULL,
                     &source.w, &source.h);

    

    int nb_images = 4;
    float zoom = 1;                      
    int offset_x = source.w / nb_images, 
        offset_y = source.h;             
    SDL_Event event;
    state.x = 0;        
    state.y = 0;        
    state.w = offset_x; 
    state.h = offset_y; 

    destination.w = offset_x * zoom; 
    destination.h = offset_y * zoom; 

    destination.y = 
        (window_dimensions.h - destination.h) / 2;
    
    while (plateau[&Pac_man->posx][]) //à modifier: tant que pac-man est vivant et qu'il reste des pac-gommes
    {
        
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:     
                if(plateau[&Pac_man->posx-1][&Pac_man->posy]==0 || plateau[&Pac_man->posx-1][&Pac_man->posy]==-1 || plateau[&Pac_man->posx-1][&Pac_man->posy]>=200)
                {
                    SDL_RenderClear(renderer);  
                    destination.x=destination.x-speed;
                    state.x += offset_x; 
                    state.x %= source.w; 
                    SDL_RenderPresent(renderer);
                }    
                break;
                case SDLK_DOWN:
                if(plateau[&Pac_man->posx+1][&Pac_man->posy]==0 || plateau[&Pac_man->posx+1][&Pac_man->posy]==-1 || plateau[&Pac_man->posx+1][&Pac_man->posy]>=200)
                {
                    SDL_RenderClear(renderer);  
                    destination.x=destination.x+speed;
                    state.x += offset_x; 
                    state.x %= source.w; 
                    SDL_RenderPresent(renderer);
                }    
                break;        
                case SDLK_RIGHT:
                if(plateau[&Pac_man->posx][&Pac_man->posy-1]==0 || plateau[&Pac_man->posx][&Pac_man->posy-1]==-1 || plateau[&Pac_man->posx][&Pac_man->posy-1]>=200)
                {
                    SDL_RenderClear(renderer);  
                    destination.y=destination.y+speed;
                    state.x += offset_x; 
                    state.x %= source.w; 
                    SDL_RenderPresent(renderer);
                }    
                break;        
                case SDLK_LEFT:
                if(plateau[&Pac_man->posx][&Pac_man->posy+1]==0 || plateau[&Pac_man->posx][&Pac_man->posy+1]==-1 || plateau[&Pac_man->posx][&Pac_man->posy+1]>=200)
                {
                    SDL_RenderClear(renderer);  
                    state.x += offset_x; 
                    state.x %= source.w; 
                    SDL_RenderPresent(renderer);
                }    
                break;        
            }
            break;
        }
    } 
}