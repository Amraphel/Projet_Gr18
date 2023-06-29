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
    int speed=1;
    while () //à modifier: tant que pac-man est vivant et qu'il reste des pac-gommes
    {
        
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                SDL_RenderClear(renderer);     
                if()    
                destination.y=destination.y-speed;
                state.x += offset_x; 
                state.x %= source.w; 
                SDL_RenderPresent(renderer); 
                break;
                case SDLK_DOWN:
                SDL_RenderClear(renderer);
                //si la case est accessible          
                destination.y=destination.y+speed;
                state.x += offset_x; 
                state.x %= source.w; 
                SDL_RenderPresent(renderer); 
                case SDLK_RIGHT:
                SDL_RenderClear(renderer);  
                //si l acase est accessible         
                destination.x=destination.x+speed;
                state.x += offset_x; 
                state.x %= source.w; 
                SDL_RenderPresent(renderer); 
                break;
                case SDLK_LEFT:
                SDL_RenderClear(renderer); 
                //si la case est accessible         
                destination.x=destination.x-speed;
                state.x += offset_x; 
                state.x %= source.w; 
                SDL_RenderPresent(renderer); 
                break;
            }
            break;
        }
    } 
}