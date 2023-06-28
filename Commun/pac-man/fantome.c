#include "fantome.h"

void play_with_texture_Blinky(SDL_Texture *my_texture,     //fonction blinky : plus court chemin vers pac-man
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

   

    int nb_images = 3;
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
    
    int speed = 1;

    //tant que pac-man est vivant et qu'il reste des pac-gommes
    {
        //calculer la distance entre blinky et pac-man
        //pour chaque case adjacente a blinky calculer la distance entre cette case et pac man
        //blinky avance sur la case qui a la distance la plus petite   
        state.x += offset_x; 
        state.x %= source.w; 
        SDL_RenderClear(renderer);           
        SDL_RenderPresent(renderer); 
        SDL_Delay(80);              
    }
    
 
   
    SDL_RenderClear(renderer); 
}

void play_with_texture_Clyde(SDL_Texture *my_texture,     //fonction clyde : prend parfois une direction aleatoire 
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

   

    int nb_images = 3;
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
    
    int speed = 1;

    //tant que pac-man est vivant et qu'il reste des pac-gommes
    {
        //meme chose que pour blinky mais a chaque mouvement il y a une probabilite qu'il choisisse une case au hasard et s'y deplace   
        state.x += offset_x; 
        state.x %= source.w; 
        SDL_RenderClear(renderer);           
        SDL_RenderPresent(renderer); 
        SDL_Delay(80);              
    }
    
  
   
    SDL_RenderClear(renderer); 
}