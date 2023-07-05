#ifndef PLATEAU
#define PLATEAU
#include "plateau.h"
#endif
#ifndef PERSO
#define PERSO
#include "perso.h"
#endif 
#include "fantome.h"
#include "SDLBasic.h"

SDL_Rect **createTabRect(SDL_Window *window, int w, int h);
void afficherPlateau(SDL_Rect **tabRect, int **plateau, int w, int h, SDL_Window *window, SDL_Renderer *renderer,int * etatAnim);
void afficherPerso(SDL_Texture* texture_perso, SDL_Renderer *renderer, SDL_Rect *rectPerso);
void animePerso(SDL_Texture* texture_perso, SDL_Renderer *renderer, SDL_Rect *rectPerso, int *etatAnim, int direction);
int collision(SDL_Rect rectPac, SDL_Rect** rectFan, int nbFan, perso_t ** tabPerso);
void animeFluide(SDL_Rect **rectPerso, int nbPerso, int *direction, int w, int h);
SDL_Texture* spriteSuperPerso(SDL_Texture **textPerso, SDL_Texture *textPersoNormal, SDL_Texture *textPersoSuper, int super);
void afficherTexteFin(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, SDL_Color couleur, char* text, int posx, int posy);
