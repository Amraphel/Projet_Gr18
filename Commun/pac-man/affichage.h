#include "plateau.h"
#include "perso.h"
#include "fantome.h"

void end_sdl(char ok,         
             char const *msg,    
             SDL_Window *window, 
             SDL_Renderer *renderer);

SDL_Window * initWindow(int x, int y, int w, int h);
SDL_Renderer *initRenderer(SDL_Window *window);

SDL_Rect **createTabRect(SDL_Window *window, int w, int h);

void afficherPlateau(SDL_Rect **tabRect, int **plateau, int w, int h, SDL_Window *window, SDL_Renderer *renderer);