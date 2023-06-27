#ifndef ARBRE
#define ARBRES
#include "arbre.h"
#endif
#ifndef POINT
#define POINT
#include "point.h"
#endif






void end_sdl(char ok,         
             char const *msg,    
             SDL_Window *window, 
             SDL_Renderer *renderer);


SDL_Rect* drawPoints(SDL_Renderer* renderer, cell_t* listeNoeud, int nombreDePoint);

SDL_Window * initWindow(int x, int y, int w, int h);
SDL_Renderer *initRenderer(SDL_Window *window);