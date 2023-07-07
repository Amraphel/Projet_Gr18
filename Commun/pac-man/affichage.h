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
void chargerTextureMap(SDL_Texture *texture,int **plateau, int nb_images, SDL_Rect **tabRect, SDL_Renderer* renderer, int i, int j, int type, int *etatAnim);
void finDeJeu(SDL_Rect rectPac, SDL_Rect **tabRectPerso, int nbFan, perso_t **tabPerso, int WINDOWW, int WINDOWL, TTF_Font* font, int**plateau, SDL_Window* window, SDL_Renderer*  renderer, int w, int h);
void destroyAllSDL(SDL_Texture* textBlin, SDL_Texture* textBlinNormal, SDL_Texture* textPac, SDL_Texture* textPacNormal, SDL_Texture* textPacSuper, SDL_Texture* textCly, SDL_Texture* textClyNormal,
    SDL_Texture* textInk, SDL_Texture* textInkNormal, SDL_Texture* textPin, SDL_Texture* textPinNormal, SDL_Texture* textFanSuper, SDL_Renderer* renderer, SDL_Window* window);
void animeFantome(perso_t** tabPerso, int numFan, SDL_Texture* textFantome, SDL_Texture* textFantomeNormal, SDL_Texture* textFantomSuper, int* etatAnim, SDL_Renderer* renderer, int* tempsMortFantome, SDL_Rect* rectFan);