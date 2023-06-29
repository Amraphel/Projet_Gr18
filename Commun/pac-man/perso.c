#include "perso.h"
perso_t* initPac_man(int ** plateau, int w, int h){
    perso_t* Pac_man = malloc(sizeof(perso_t));
    Pac_man->id=99;
    Pac_man->etat=0;
    coordPlat(plateau, w, h, Pac_man->id, &Pac_man->posX, &Pac_man->posY);
    return Pac_man;
}


void mouv_Pac_man(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, int direction, int *posX, int *posY)
{
    SDL_Rect
        source = {0},            
        window_dimensions = {0}, 
        destination = {0},       
        state = {0};             

    SDL_GetWindowSize(window, 
                      &window_dimensions.w,
                      &window_dimensions.h);
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);

    

    int nb_images = 4;
    float zoom = 1;      
    int offset_x = source.w / nb_images, 
        offset_y = source.h;     
    /*        
    SDL_Event event;
    state.x = 0;        
    state.y = 0;        
    state.w = offset_x; 
    state.h = offset_y; 
    state.x += offset_x; 
    state.x %= source.w; 
    */
    destination.w = offset_x * zoom; 
    destination.h = offset_y * zoom; 
    destination.x = *posX;
    destination.y = *posY;

    // movePersoInPlateau(plateau, posX, posY, 99, direction);         
    SDL_RenderCopy(renderer, my_texture, &state, &destination); 
}