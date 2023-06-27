#ifndef CLASSIQUE
#define CLASSIQUE
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#endif






void end_sdl(char ok,         
             char const *msg,    
             SDL_Window *window, 
             SDL_Renderer *renderer);


SDL_Rect* drawPoints(SDL_Renderer* renderer, cell_t* listeNoeud, int nombreDePoint);

SDL_Window * initWindow(int x, int y, int w, int h);