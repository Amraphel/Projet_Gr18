// #include "affichage.h"
// #include "fantome.h"
// #include "plateau.h"

// // #define WINDOWL 700
// // #define WINDOWW 700

// int main()
// {
//     int w;
//     int h;
//     time_t t;
//     time(&t);

//     srand(t);
//     int **plateau = loadPlateau("./source/lvl/lvl1.txt", &w, &h);
//     int WINDOWW = w * (700 / w);
//     int WINDOWL = h * (700 / h);
//     printPlateau(plateau, w, h);
//     if (SDL_Init(SDL_INIT_VIDEO) != 0)
//     {
//         SDL_Log("Error : SDL initialisation - %s\n",
//                 SDL_GetError());
//         exit(EXIT_FAILURE);
//     }

//     SDL_bool
//         program_on = SDL_TRUE,
//         event_utile = SDL_FALSE;

//     SDL_Event
//         event;

//     SDL_Window *window = initWindow(200, 100, WINDOWW, WINDOWL);
//     SDL_Renderer *renderer = initRenderer(window);
//     SDL_Rect **tabRect = createTabRect(window, w, h);
//     perso_t *Pac_man = initPac_man(plateau, w, h);
//     perso_t *Blinky = initBlinky(plateau, w, h);
//     perso_t *Clyde = initClyde(plateau, w, h);
//     perso_t ** tabPerso= malloc(sizeof(perso_t*)*3);
//     tabPerso[0] = Pac_man;
//     tabPerso[1] = Blinky;
//     tabPerso[2] = Clyde;

//     int * dir = malloc(sizeof(int)*3);
//     dir[0]=0;
//     dir[1]=0;
//     dir[2]=0;

//     int super = 0;
//     SDL_Texture *textPac = load_texture_from_image("./source/Pac-man.png", window, renderer);
//     SDL_Texture *textBlin = load_texture_from_image("./source/Blinky.png", window, renderer);
//     SDL_Texture *textCly = load_texture_from_image("./source/Clyde.png", window, renderer);
//     SDL_Rect rectPac = {Pac_man->posY * WINDOWL / h, Pac_man->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};
//     SDL_Rect rectBlin = {Blinky->posY * WINDOWL / h, Blinky->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};
//     SDL_Rect rectCly = {Clyde->posY * WINDOWL / h, Clyde->posX * WINDOWW / w, WINDOWL / h, WINDOWW / w};

//     int nbFan = 2;
//     SDL_Rect** tabRectPerso= malloc(sizeof(SDL_Rect*)*3);
//     tabRectPerso[0]=&rectPac;
//     tabRectPerso[1] = &rectBlin;
//     tabRectPerso[2] = &rectCly;

//     if (Blinky->posX != 0)
//     {
//         afficherPerso(textBlin, renderer, &rectBlin);
//     }

//     afficherPerso(textPac, renderer, &rectPac);
//     if (Clyde->posX != 0)
//     {
//         afficherPerso(textCly, renderer, &rectCly);
//     }

//     if (TTF_Init() < 0)
//         end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

//     TTF_Font *font = NULL;

//     font = TTF_OpenFont("./Front/BadComic-Regular.ttf", 90);
//     if (font == NULL)
//     {
//         end_sdl(0, "Can't load font", window, renderer);
//     }

    
//     int speedMove = 100000;
//     int speed = speedMove/10;
//     int speedDep= speedMove/10;
//     int test=1;
//     int i = 0;
//     int move = 0;
//     int animeF=0;
//     int mort = 0;
//     int etatAnim = 0;
//     int keyPressed = 0;
//     int direction = 0;
//     Pac_man->etat = 0;

//     int pause = 0;
//     SDL_RenderPresent(renderer);

//     while (program_on)
//     {
//         event_utile = SDL_FALSE;
//         while (!event_utile && SDL_PollEvent(&event))
//         {
//             switch (event.type)
//             {
//             case SDL_QUIT:
//                 program_on = SDL_FALSE;
//                 event_utile = SDL_TRUE;
//                 break;
//             case SDL_KEYDOWN:
//                 switch (event.key.keysym.sym)
//                 {
//                 case SDLK_ESCAPE:
//                 case SDLK_q:
//                     program_on = 0;
//                     event_utile = SDL_TRUE;

//                     break;
//                 case SDLK_DOWN:

//                     if (collision(rectPac, tabRectPerso, nbFan) != 1 && gom_exist(plateau, w, h) == 0 && pause != 1)
//                     {
//                         if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 1) && !keyPressed)
//                         {
//                             direction= 1;
//                         }
//                     }
//                     break;
//                 case SDLK_UP:
//                     if (collision(rectPac, tabRectPerso, nbFan) != 1 && gom_exist(plateau, w, h) == 0 && pause != 1)
//                     {
//                         if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 3) && !keyPressed)
//                         {
//                             direction = 3;
//                         }
//                     }
//                     break;
//                 case SDLK_RIGHT:
//                     if (collision(rectPac, tabRectPerso, nbFan) != 1 && gom_exist(plateau, w, h) == 0 && pause != 1)
//                     {
//                         if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 4) && !keyPressed)
//                         {
//                            direction = 4;
//                         }
//                     }
//                     break;
//                 case SDLK_LEFT:
//                     if (collision(rectPac, tabRectPerso, nbFan) != 1 && gom_exist(plateau, w, h) == 0 && pause != 1)
//                     {
//                         if (movePossible(plateau, Pac_man->posX, Pac_man->posY, 2) && !keyPressed)
//                         {
//                             direction = 2;
//                         }
//                     }
//                     break;
//                 case SDLK_SPACE:
//                     if (super == 0)
//                     {
//                         textPac = load_texture_from_image("./source/SuperPac-man.png", window, renderer);
//                         super = 1;
//                     }
//                     else
//                     {
//                         textPac = load_texture_from_image("./source/Pac-man.png", window, renderer);
//                         super = 0;
//                     }
//                     break;
//                 case SDLK_p:
//                     if (pause == 1)
//                     {
//                         pause = 2;
//                     }
//                     else
//                     {
//                         pause = 1;
//                     }
//                     break;
//                 case SDLK_s:
//                     savePlateau(plateau, w, h);
//                     break;
//                 default:
//                     break;
//                 }
//             }
//         }
//         if (collision(rectPac, tabRectPerso, nbFan)  != 1 && gom_exist(plateau, w, h) == 0 && pause != 1)
//         {
//             if (move == 0)
//             {
                
//                 dir[0] =movePacmanIA(plateau, Pac_man);
//                 if (Blinky->posX != 0)
//                 {
//                    dir[1]= moveBlinky(window, plateau, w, h, Blinky, Pac_man, &rectBlin, &mort);
//                 }
//                 if (Clyde->posX != 0)
//                 {
//                    dir[2]= moveClyde(window, plateau, w, h, Clyde, Pac_man, &rectCly, &mort);
//                 }
//                 for(int j=0; j<3; j++){
//                     movePersoInPlateau(plateau,&tabPerso[j]->posX, &tabPerso[j]->posY, tabPerso[j]->id,dir[j], &mort);
//                 }
//                 direction=0;
//             }
//             move = (move + 1) % speedMove;
//             if(animeF==0){
//                 afficherPlateau(tabRect, plateau, w, h, window, renderer);
//                 animeFluide(tabRectPerso,3, dir, plateau, tabPerso);
//                 //  SDL_RenderPresent(renderer);
//             }
//             animeF= (animeF+1) % speedDep;
//             if (i == 0)
//             {
//                 afficherPlateau(tabRect, plateau, w, h, window, renderer);
//                 animePerso(textPac, renderer, &rectPac, &etatAnim, Pac_man->etat);
//                 if (Blinky->posX != 0)
//                 {
//                     animePerso(textBlin, renderer, &rectBlin, &etatAnim, Blinky->etat);
//                 }

//                 if (Clyde->posX != 0)
//                 {
//                     animePerso(textCly, renderer, &rectCly, &etatAnim, Clyde->etat);
//                 }
//                 if (collision(rectPac, tabRectPerso, nbFan) == 1)
//                 {
//                     afficherGameOver(window, renderer, font);
//                 }
//                 if (gom_exist(plateau, w, h) != 0)
//                 {
//                     afficherBravo(window, renderer, font);
//                 }
//                 SDL_RenderPresent(renderer);
//             }
//             i = (i + 1) % speed;
//         }
//     }


//     freePlateau(plateau, w);



//     free(tabRectPerso);
//     SDL_DestroyTexture(textCly);
//     SDL_DestroyTexture(textPac);
//     SDL_DestroyTexture(textBlin);
//     end_sdl(1, "Normal ending", window, renderer);
//     for(int i =0; i<3; i++){
//         free(tabPerso[i]);
//         free(tabRect[i]);
//     }
//     free(tabPerso);
//     free(tabRect);

//     return 0;
// }