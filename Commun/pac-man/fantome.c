#include "fantome.h"

perso_t *initBlinky(int **plateau, int w, int h)
{
    perso_t *blinky = malloc(sizeof(perso_t));
    blinky->id = 200;
    coordPlat(plateau, w, h, blinky->id, &blinky->posX, &blinky->posY);

    return blinky;
}

perso_t *initClyde(int **plateau, int w, int h)
{
    perso_t *clyde = malloc(sizeof(perso_t));
    clyde->id = 210;
    coordPlat(plateau, w, h, clyde->id, &clyde->posX, &clyde->posY);

    return clyde;
}

int heuriBasique(int x, int y, int pacX, int pacY)
{
    return pow(pacX - x, 2) + pow(pacY - y, 2);
}


void creerHeuri(int ** heuri, int** plateau, int  x,int y,int val){
    heuri[x][y]=val;
    for (int i = 1; i < 5; i++)
    {
        int newX=x;
        int newY=y;
        if (movePossible(plateau, x, y, i))
        {
            switch (i)
            {
            case 1:
                newX+=1;
                
                break;
            case 2:
                newY-=1;
                break;
            case 3:
                newX-=1;
                break;
            case 4:
                newY+=1;
                break;

            default:
                break;
            }
            if(heuri[newX][newY]==-1 || heuri[newX][newY]>val+1){
                    creerHeuri(heuri, plateau,newX, newY,val+1);
            }
        }
    }

}


int ** heuristique(int** plateau,int pacX,int pacY,int w,int h){
    int ** heuri=malloc(sizeof(int*)*w);
    for(int i =0; i<w; i++){
        int * ligne= malloc(sizeof(int)*h);
        heuri[i]=ligne;
        for(int j=0; j<h; j++){
            heuri[i][j]=-1;
        }
    }
    creerHeuri(heuri, plateau, pacX, pacY, 0);
    return heuri;
}

int getNextMove(int **plateau,int** heuristique, int fantX, int fantY)
{
    int dir = 0;
    int heuri = -1;
    for (int i = 1; i < 5; i++)
    {
        if (movePossible(plateau, fantX, fantY, i))
        {
            int newHeuri = 0;
            switch (i)
            {
            case 1:
                newHeuri = heuristique[fantX+1][fantY];
                break;
            case 2:
                newHeuri =heuristique[fantX][fantY-1];
                break;
            case 3:
                newHeuri =heuristique[fantX-1][fantY]; 
                break;
            case 4:
                newHeuri =heuristique[fantX][fantY+1];
                break;

            default:
                break;
            }
            if (heuri == -1 || heuri > newHeuri)
            {
                heuri = newHeuri;
                dir = i;
            }
        }
    }
    return dir;
}

void moveBlinky( // fonction blinky : plus court chemin vers pac-man
    SDL_Window *window,
    int **plateau, int w, int h, perso_t *Blinky, perso_t *Pac_man, SDL_Rect *rectBlin, int* mort)
{
    SDL_Rect
        window_dimensions = {0};

    int ** heuri= heuristique(plateau,Pac_man->posX, Pac_man->posY, w,h);
    
    SDL_GetWindowSize(window,
                      &window_dimensions.w,
                      &window_dimensions.h);

    int move = getNextMove(plateau,heuri, Blinky->posX, Blinky->posY);
    switch ((move))
    {
    case 1:
        movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 1, mort);
        rectBlin->y += window_dimensions.h / h;
        break;
    case 2:
        movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 2, mort);
        rectBlin->x -= window_dimensions.w / w;
        break;

    case 3:
        movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 3, mort);
        rectBlin->y -= window_dimensions.h / h;
        break;
    case 4:
        movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 4, mort);
        rectBlin->x += window_dimensions.w / w;
        break;

    default:
        break;
    }
}

// void play_with_texture_Clyde(SDL_Texture *my_texture,     //fonction clyde : prend parfois une direction aleatoire
//                          SDL_Window *window,
//                          SDL_Renderer *renderer)
// {
//     SDL_Rect
//         source = {0},
//         window_dimensions = {0},
//         destination = {0},
//         state = {0};

//     SDL_GetWindowSize(window,
//                       &window_dimensions.w,
//                       &window_dimensions.h);
//     SDL_QueryTexture(my_texture,
//                      NULL, NULL,
//                      &source.w, &source.h);

//     int nb_images = 3;
//     float zoom = 1;
//     int offset_x = source.w / nb_images,
//         offset_y = source.h;
//     SDL_Event event;
//     state.x = 0;
//     state.y = 0;
//     state.w = offset_x;
//     state.h = offset_y;

//     destination.w = offset_x * zoom;
//     destination.h = offset_y * zoom;

//     destination.y =
//         (window_dimensions.h - destination.h) / 2;

//     int speed = 1;

//     //tant que pac-man est vivant et qu'il reste des pac-gommes
//     {
//         //meme chose que pour blinky mais a chaque mouvement il y a une probabilite qu'il choisisse une case au hasard et s'y deplace
//         state.x += offset_x;
//         state.x %= source.w;
//         SDL_RenderClear(renderer);
//         SDL_RenderPresent(renderer);
//         SDL_Delay(80);
//     }

//     SDL_RenderClear(renderer);
// }