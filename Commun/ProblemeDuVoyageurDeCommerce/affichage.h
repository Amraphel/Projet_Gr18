#ifndef GRAPHE
#define GRAPHE
#include "graphe.h"
#endif
#ifndef POINT
#define POINT
#include "point.h"
#endif






void end_sdl(char ok,         
             char const *msg,    
             SDL_Window *window, 
             SDL_Renderer *renderer);


SDL_Rect* createPoints(point_t* listPoint, int nombreDePoint);
void drawPoints(SDL_Renderer* renderer, SDL_Rect* tabPoint,int nombreDePoint,int* tabType);
SDL_Window * initWindow(int x, int y, int w, int h);
SDL_Renderer *initRenderer(SDL_Window *window);
void drawLine(SDL_Renderer* renderer, cell_t* graphe, int nbNoeud);
void drawGraphe(SDL_Renderer* renderer, SDL_Rect* tabPoint,cell_t* graphe,int nbNoeud,int* tabType);
void click(int* tabType, point_t* listPoint, int* numActuel, int nbNoeud, float clickx, float clicky,int* poidsParcours, int ** mat);
void resetVisitabe(int* tabType, int nbNoeud);