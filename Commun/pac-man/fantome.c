#include "fantome.h"

perso_t *initBlinky(int **plateau, int w, int h)
{
    perso_t *blinky = malloc(sizeof(perso_t));
    blinky->id = 200;
    coordPlat(plateau, w, h, blinky->id, &blinky->posX, &blinky->posY);

    return blinky;
}

int heuriBasique(int x, int y, int pacX, int pacY)
{
    return abs(pacX - x + pacY - y);
}

// int getNextMove(int **plateau, int fantX, int fantY, int pacX, int pacY)
// {
//     int dir = 0;
//     int heuri = -1;
//     for (int i = 1; i < 5; i++)
//     {
//         if (movePossible(plateau,fantX, fantY, i))
//         {
//             int newHeuri = heuriBasique(fantX, fantY, pacX, pacY);
//             if (heuri == -1 || heuri > newHeuri)
//             {
//                 heuri = newHeuri;
//                 dir = i;
//             }
//         }
//     }
// }

// void moveBlinky(SDL_Texture *my_texture, // fonction blinky : plus court chemin vers pac-man
//                 SDL_Window *window,
//                 SDL_Renderer *renderer, int plateau, int w, int h, perso_t *Blinky, perso_t *Pac_man)
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
//     int offset_x = source.w / nb_images,
//         offset_y = source.h;
//     SDL_Event event;
//     state.x = 0;
//     state.y = 0;
//     state.w = offset_x;
//     state.h = offset_y;

//     destination.w = offset_x;
//     destination.h = offset_y;

//     int move = getNextMove(plateau, Blinky->posX, Blinky->posY, Pac_man->posX, Pac_man->posY);
//     switch ((move))
//     {
//     case 1:
//         Blinky->posY+=1;
//         break;
//     case 2:
//         Blinky->posX-=1;
//         break;

//     case 3:
//         Blinky->posY-=1;
//         break;
//     case 4:
//         Blinky->posX+=1;
//         break;

//     default:
//         break;
//     }
//     destination.x = Blinky->posX * window_dimensions.w;
//     destination.y = Blinky->posY * window_dimensions.h;

//     state.x += offset_x;
//     state.x %= source.w;
//     SDL_RenderClear(renderer);
//     SDL_RenderPresent(renderer);
// }

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