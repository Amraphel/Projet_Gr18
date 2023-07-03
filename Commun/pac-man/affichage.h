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
void afficherPlateau(SDL_Rect **tabRect, int **plateau, int w, int h, SDL_Window *window, SDL_Renderer *renderer);
void afficherPerso(SDL_Texture* my_texture, SDL_Renderer *renderer, SDL_Rect *RectPac);
void animePerso(SDL_Texture* skin, SDL_Renderer *renderer, SDL_Rect *rectPerso, int *etatAnim, int dir);
void afficherGameOver(SDL_Window* window, SDL_Renderer *renderer, TTF_Font *font);
void afficherBravo(SDL_Window* window, SDL_Renderer *renderer, TTF_Font *font);
int collision(SDL_Rect rectPac, SDL_Rect** rectFan, int nbFan);
void animeFluide(SDL_Rect **rectPerso, int nbPerso, int *dir, int **plateau, perso_t **tabPerso);