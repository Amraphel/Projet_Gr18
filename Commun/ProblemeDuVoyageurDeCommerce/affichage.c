#include "affichage.h"

void end_sdl(char ok,
             char const *msg,
             SDL_Window *window,
             SDL_Renderer *renderer)
{
    char msg_formated[255];
    int l;

    if (!ok)
    { // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();

    if (!ok)
    {
        exit(EXIT_FAILURE);
    }
}

SDL_Window *initWindow(int x, int y, int w, int h)
{
    SDL_Window *window = NULL;

    
    window = SDL_CreateWindow(
        "Fenêtre",
        x, y,
        w, h,
        SDL_WINDOW_RESIZABLE);

    if (window == NULL)
    {
        SDL_Log("Error : SDL window creation - %s\n",
                SDL_GetError()); // échec de la création de la fenêtre
        SDL_Quit();              // On referme la SDL
        exit(EXIT_FAILURE);
    }

    return window;
}

SDL_Renderer *initRenderer(SDL_Window *window)
{
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return renderer;
}

SDL_Rect* createPoints(point_t* listPoint, int nombreDePoint){
    SDL_Rect* tabPoint= malloc(sizeof(SDL_Rect)*nombreDePoint);
    int i=0;
    while(i<nombreDePoint){
        SDL_Rect point;

        point.x= listPoint[i].x;
        point.y=listPoint[i].y;
        point.w=20;
        point.h=20;
        tabPoint[i]=point;
        i++;
    }
    return tabPoint;
}

void drawPoints(SDL_Renderer* renderer, SDL_Rect* tabPoint,int nombreDePoint, int* tabType){
    for(int i=0; i<nombreDePoint; i++){
        switch (tabType[i])
        {
        case 0: //non visite (noir)
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            break;

        case 2://visite (bleu)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            break;

        case 1: //visitable (vert)
        case 3: //visite et visitable (vert)
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            break;

        case 4: //actuel (rouge)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            break;
        
        default:
            break;
        }
        SDL_RenderFillRect(renderer,&tabPoint[i] );
    }
}


void drawLine(SDL_Renderer* renderer, cell_t* graphe, int nbNoeud){
    int i;
    int j;
    for(i=0; i<nbNoeud; i++){
        for(j=0; j<nbNoeud; j++){
            if(graphe[i].lien[j]>0){
                SDL_RenderDrawLine(renderer, graphe[i].point.x+10, graphe[i].point.y+10,
                                                graphe[j].point.x+10, graphe[j].point.y+10);
            }
        }
    }
}

void drawGraphe(SDL_Renderer* renderer, SDL_Rect* tabPoint,cell_t* graphe,int nbNoeud, int* tabType){
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    drawPoints(renderer,tabPoint,nbNoeud,tabType);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    drawLine(renderer,graphe,nbNoeud);
    SDL_RenderPresent(renderer);
}

void click(int* tabType, point_t* listPoint, int* numActuel, int nbNoeud, float clickx, float clicky, int* poidsParcours, int ** mat)
{
    int i = 0;
    int estTrouve = 0;
    while( estTrouve ==0 && i < nbNoeud)
    {
        if(clickx < listPoint[i].x + 20 && clickx > listPoint[i].x && clicky < listPoint[i].y + 20 && clicky > listPoint[i].y)
        {
            if(tabType[i] == 1 || tabType[i] == 3)
            {
                tabType[*numActuel] = 3;
                tabType[i] = 4;
                resetVisitabe(tabType, nbNoeud);
                *poidsParcours += mat[i][*numActuel];
                *numActuel = i;
                estTrouve = 1;
            }
        }
        i++;
    }
}

void resetVisitabe(int* tabType, int nbNoeud)
{
    for(int i = 0; i < nbNoeud; i++)
    {
        if(tabType[i] == 1)
        {
            tabType[i] = 0;
        }
        else if (tabType[i]== 3)
        {
            tabType[i] = 2;
        }
        
    }
}

void score(int poidsParcours, int poidsFourmis, int poidsRecuit)
{
    
}

void affichageScore(SDL_Window* window, SDL_Renderer *renderer)
{
    TTF_Font *font = NULL;

    font = TTF_OpenFont("./Front/BadComic-Regular.ttf", 20);
    if (font == NULL)
    {
        end_sdl(0, "Can't load font", window, renderer);
    }
    SDL_Color color = {20, 0, 40, 255};
    SDL_Surface *text_surface = NULL;
    text_surface = TTF_RenderText_Blended(font, "taper p ou f pour aller a la prochaine fenetre", color); // création du texte dans la surface
    if (text_surface == NULL)
    {
        end_sdl(0, "Can't create text surface", window, renderer);
    }

    // Création de la texture du text
    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL)
    {
        end_sdl(0, "Can't create texture from surface", window, renderer);
    }

    SDL_FreeSurface(text_surface); // la surface ne sert plus à rien

    SDL_Rect pos = {10, 0, 0, 0};                               // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);         // Ecriture du texte dans le renderer
    SDL_DestroyTexture(text_texture);
    SDL_RenderPresent(renderer);
}