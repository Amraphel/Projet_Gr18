#ifndef BASE
#define BASE
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#endif


void end_sdl(char ok,         
             char const *msg,    
             SDL_Window *window, 
             SDL_Renderer *renderer);

SDL_Window * initWindow(int x, int y, int w, int h);
SDL_Renderer *initRenderer(SDL_Window *window);

SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer);
