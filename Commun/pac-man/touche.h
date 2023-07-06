#ifndef PLATEAU
#define PLATEAU
#include "plateau.h"
#endif
#ifndef PERSO
#define PERSO
#include "perso.h"
#endif 
#ifndef AFFICHAGE
#define AFFICHAGE
#include "affichage.h"
#endif

int deplacement(int move, perso_t* Pac_man, int** plateau, SDL_Rect ** tabRectPerso, perso_t** tabPerso, int nbFan, SDL_Rect rectPac, int w, int h, int pause, int keyPressed);
void destroyAllSDL(SDL_Texture* textBlin, SDL_Texture* textBlinNormal, SDL_Texture* textPac, SDL_Texture* textPacNormal, SDL_Texture* textPacSuper, SDL_Texture* textCly, SDL_Texture* textClyNormal,
    SDL_Texture* textInk, SDL_Texture* textInkNormal, SDL_Texture* textPin, SDL_Texture* textPinNormal, SDL_Texture* textFanSuper, SDL_Renderer* renderer, SDL_Window* window);
void finDeJeu(SDL_Rect rectPac, SDL_Rect **tabRectPerso, int nbFan, perso_t **tabPerso, int WINDOWW, int WINDOWL, TTF_Font* font, int**plateau, SDL_Window* window, SDL_Renderer*  renderer, int w, int h);
