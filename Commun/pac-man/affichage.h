#include "plateau.h"
#ifndef PERSO
#define PERSO
#include "perso.h"
#endif 
#include "fantome.h"
#include "SDLBasic.h"

SDL_Rect **createTabRect(SDL_Window *window, int w, int h);
void afficherPlateau(SDL_Rect **tabRect, int **plateau, int w, int h, SDL_Window *window, SDL_Renderer *renderer);
void afficherPerso(perso_t *perso, SDL_Window *window, SDL_Renderer *renderer, SDL_Rect* RectPac);
void animePerso(perso_t *perso, SDL_Window *window, SDL_Renderer *renderer, SDL_Rect *rectPero, int * etatAnim);