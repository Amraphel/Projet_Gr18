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

void creerHeuri(int **heuri, int **plateau, int x, int y, int val)
{
    heuri[x][y] = val;
    for (int i = 1; i < 5; i++)
    {
        int newX = x;
        int newY = y;
        if (movePossible(plateau, x, y, i))
        {
            switch (i)
            {
            case 1:
                newX += 1;

                break;
            case 2:
                newY -= 1;
                break;
            case 3:
                newX -= 1;
                break;
            case 4:
                newY += 1;
                break;

            default:
                break;
            }
            if (heuri[newX][newY] == -1 || heuri[newX][newY] > val + 1)
            {
                creerHeuri(heuri, plateau, newX, newY, val + 1);
            }
        }
    }
}

int **heuristique(int **plateau, int pacX, int pacY, int w, int h)
{
    int **heuri = malloc(sizeof(int *) * w);
    for (int i = 0; i < w; i++)
    {
        int *ligne = malloc(sizeof(int) * h);
        heuri[i] = ligne;
        for (int j = 0; j < h; j++)
        {
            heuri[i][j] = -1;
        }
    }
    creerHeuri(heuri, plateau, pacX, pacY, 0);
    return heuri;
}

void freeHeuri(int **heuri, int w)
{
    for (int i = 0; i < w; i++)
    {
        free(heuri[i]);
        heuri[i] = NULL;
    }
    free(heuri);
    heuri = NULL;
}

int getNextMove(int **plateau, int **heuristique, int fantX, int fantY)
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
                newHeuri = heuristique[fantX + 1][fantY];
                break;
            case 2:
                newHeuri = heuristique[fantX][fantY - 1];
                break;
            case 3:
                newHeuri = heuristique[fantX - 1][fantY];
                break;
            case 4:
                newHeuri = heuristique[fantX][fantY + 1];
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

void moveRandom(int **plateau, SDL_Window *window, int w, int h, perso_t *Clyde, int *mort, SDL_Rect *rectCly)
{
    int i = rand() % 4 + 1;
    SDL_Rect
        window_dimensions = {0};
    SDL_GetWindowSize(window,
                      &window_dimensions.w,
                      &window_dimensions.h);
    while (!movePossible(plateau, Clyde->posX, Clyde->posY, i))
    {
        i = rand() % 4 + 1;
    }

    {
        switch (i)
        {
        case 1:
            movePersoInPlateau(plateau, &Clyde->posX, &Clyde->posY, Clyde->id, 1, mort);
            rectCly->y += window_dimensions.h / h;
            Clyde->etat = 3;
            break;
        case 2:
            movePersoInPlateau(plateau, &Clyde->posX, &Clyde->posY, Clyde->id, 2, mort);
            rectCly->x -= window_dimensions.w / w;
            Clyde->etat = 2;
            break;
        case 3:
            movePersoInPlateau(plateau, &Clyde->posX, &Clyde->posY, Clyde->id, 3, mort);
            rectCly->y -= window_dimensions.h / h;
            Clyde->etat = 1;
            break;
        case 4:
            movePersoInPlateau(plateau, &Clyde->posX, &Clyde->posY, Clyde->id, 4, mort);
            rectCly->x += window_dimensions.w / w;
            Clyde->etat = 0;
            break;

        default:
            break;
        }
    }
}

void moveBlinky( // fonction blinky : plus court chemin vers pac-man
    SDL_Window *window,
    int **plateau, int w, int h, perso_t *Blinky, perso_t *Pac_man, SDL_Rect *rectBlin, int *mort)
{
    SDL_Rect
        window_dimensions = {0};

    int **heuri = heuristique(plateau, Pac_man->posX, Pac_man->posY, w, h);

    SDL_GetWindowSize(window,
                      &window_dimensions.w,
                      &window_dimensions.h);

    int move = getNextMove(plateau, heuri, Blinky->posX, Blinky->posY);
    switch ((move))
    {
    case 1:
        movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 1, mort);
        rectBlin->y += window_dimensions.h / h;
        Blinky->etat = 3;
        break;
    case 2:
        movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 2, mort);
        rectBlin->x -= window_dimensions.w / w;
        Blinky->etat = 2;
        break;

    case 3:
        movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 3, mort);
        rectBlin->y -= window_dimensions.h / h;
        Blinky->etat = 1;
        break;
    case 4:
        movePersoInPlateau(plateau, &Blinky->posX, &Blinky->posY, Blinky->id, 4, mort);
        rectBlin->x += window_dimensions.w / w;
        Blinky->etat = 0;
        break;

    default:
        break;
    }

    freeHeuri(heuri,w);
}

void moveClyde(SDL_Window *window, int **plateau, int w, int h, perso_t *Clyde, perso_t *Pac_man, SDL_Rect *rectClyde, int *mort)
{
    int i = rand() % 100 + 1;
    if (i < 25)
    {
        moveRandom(plateau, window, w, h, Clyde, mort, rectClyde);
    }
    else
    {
        moveBlinky(window, plateau, w, h, Clyde, Pac_man, rectClyde, mort);
    }
}